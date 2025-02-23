#include "../include/Longnum.hpp"
#include "../include/lnum_utils.hpp"

#include <iostream>

void LongNumber::MakeDeque(void *ptr)
{
	auto parts = static_cast<LongNumParts *>(ptr);
	const std::string BinaryString = parts->IntPart + parts->FracPart;

	if (BinaryString.length() % 32 != 0)
		throw std::invalid_argument("Binary string length must be a multiple of 32.\n");

	num = PushToDeque(BinaryString);
	IntAccuracy_increased = (uint16_t)((parts->IntPart).length() / 32ull);
	FracAccuracy_increased = (uint16_t)((parts->FracPart).length() / 32ull);
	delete parts;
}

void LongNumber::NormalizeDigits(uint16_t IntPart, uint16_t FracPart)
{
	while (FracAccuracy_increased != FracPart)
	{
		num->push_back(0ull);
		FracAccuracy_increased++;
	}

	while (IntAccuracy_increased != IntPart)
	{
		num->push_front(0ull);
		IntAccuracy_increased++;
	}
}

void LongNumber::NormalizeAccuracy()
{
	if ((uint16_t)num->size() == IntAccuracy_increased + FracAccuracy_increased + 1)
		IntAccuracy_increased++;

	size_t index = 0;
	while (index < IntAccuracy_increased && (*num)[index] == 0)
		index++;
	if (index != IntAccuracy_increased)
	{
		unsigned int new_acc = 64u - (uint16_t)__builtin_clzll((*num)[index]);
		new_acc += 32u * (uint16_t)(IntAccuracy_increased - (uint16_t)index - 1u);
		if (new_acc > IntAccuracy)
		{
			IntAccuracy = (uint16_t)new_acc;
			std::cout << "Warning[summarize]: IntAccuracy has been increased up to " + std::to_string(new_acc) + " binary digits."
					  << std::endl;
		}
	}
}

LongNumber::LongNumber() : IntAccuracy(32),
						   FracAccuracy(64)
{
	const std::string str_num = "0";
	LongNumParts *my_num_parts = DecToBinary(str_num, (int)IntAccuracy, (int)FracAccuracy);

	uint16_t act_int_accuracy = (uint16_t)((my_num_parts->IntPart).length() - (my_num_parts->IntPart).find_first_not_of('0'));

	if (IntAccuracy < act_int_accuracy && (my_num_parts->IntPart).find_first_not_of('0') != (my_num_parts->IntPart).npos)
	{
		IntAccuracy = act_int_accuracy;
		std::cout << "Warning[constructor]: IntAccuracy has been increased up to " + std::to_string(act_int_accuracy) + " binary digits."
				  << std::endl;
	}

	MakeDeque(my_num_parts);
}

LongNumber::LongNumber(uint16_t IntAcc, uint16_t FracAcc) : IntAccuracy(IntAcc),
															FracAccuracy(FracAcc)
{
	const std::string str_num = "0";
	LongNumParts *my_num_parts = DecToBinary(str_num, (int)IntAccuracy, (int)FracAccuracy);

	uint16_t act_int_accuracy = (uint16_t)((my_num_parts->IntPart).length() - (my_num_parts->IntPart).find_first_not_of('0'));

	if (IntAccuracy < act_int_accuracy && (my_num_parts->IntPart).find_first_not_of('0') != (my_num_parts->IntPart).npos)
	{
		IntAccuracy = act_int_accuracy;
		std::cout << "Warning[constructor]: IntAccuracy has been increased up to " + std::to_string(act_int_accuracy) + " binary digits."
				  << std::endl;
	}

	MakeDeque(my_num_parts);
}

LongNumber::LongNumber(const char *input = "0", uint16_t IntAcc = 32, uint16_t FracAcc = 64) : IntAccuracy(IntAcc),
																							   FracAccuracy(FracAcc)
{
	std::string str_num = std::string(input);
	if (input[0] == '-')
	{
		str_num.erase(0, 1);
		sign = -1;
	}

	LongNumParts *my_num_parts = DecToBinary(str_num, (int)IntAccuracy, (int)FracAccuracy);

	uint16_t act_int_accuracy = (uint16_t)((my_num_parts->IntPart).length() - (my_num_parts->IntPart).find_first_not_of('0'));

	if (IntAccuracy < act_int_accuracy && (my_num_parts->IntPart).find_first_not_of('0') != (my_num_parts->IntPart).npos)
	{
		IntAccuracy = act_int_accuracy;
		std::cout << "Warning[constructor]: IntAccuracy has been increased up to " + std::to_string(act_int_accuracy) + " binary digits."
				  << std::endl;
	}

	MakeDeque(my_num_parts);
}

LongNumber::LongNumber(const LongNumber &other) :

												  IntAccuracy(other.IntAccuracy),
												  FracAccuracy(other.FracAccuracy),
												  IntAccuracy_increased(other.IntAccuracy_increased),
												  FracAccuracy_increased(other.FracAccuracy_increased),
												  sign(other.sign)
{
	num = new std::deque<unsigned long long>(*other.num);
}

LongNumber::LongNumber(LongNumber &&other) noexcept :

													  IntAccuracy(other.IntAccuracy),
													  FracAccuracy(other.FracAccuracy),
													  IntAccuracy_increased(other.IntAccuracy_increased),
													  FracAccuracy_increased(other.FracAccuracy_increased),
													  sign(other.sign),
													  num(other.num)
{
	if (this != &other)
		other.num = nullptr;
}

LongNumber::~LongNumber()
{
	delete num;
}

LongNumber &LongNumber::operator=(const LongNumber &other)
{
	if (this == &other)
		return *this;

	delete num;
	IntAccuracy = other.IntAccuracy;
	IntAccuracy_increased = other.IntAccuracy_increased;
	FracAccuracy = other.FracAccuracy;
	FracAccuracy_increased = other.FracAccuracy_increased;
	sign = other.sign;

	num = new std::deque<unsigned long long>(*other.num);
	return *this;
}

LongNumber &LongNumber::operator=(LongNumber &&other)
{
	if (this == &other)
		return *this;

	delete num;
	IntAccuracy = other.IntAccuracy;
	IntAccuracy_increased = other.IntAccuracy_increased;
	FracAccuracy = other.FracAccuracy;
	FracAccuracy_increased = other.FracAccuracy_increased;
	sign = other.sign;

	num = other.num;
	other.num = nullptr;
	return *this;
}

LongNumber LongNumber::operator-() const
{
	LongNumber res(*this);
	res.sign *= -1;
	return res;
}

bool LongNumber::operator==(const LongNumber &other) const
{
	LongNumber temp1 = *this;
	LongNumber temp2 = other;

	uint16_t MaxFrac = std::max(temp1.FracAccuracy_increased, temp2.FracAccuracy_increased);
	uint16_t MaxInt = std::max(temp1.IntAccuracy_increased, temp2.IntAccuracy_increased);

	temp1.NormalizeDigits(MaxInt, MaxFrac);
	temp2.NormalizeDigits(MaxInt, MaxFrac);

	if (IsZeroDeq(temp1.num) && IsZeroDeq(temp2.num))
		return true;

	return *temp1.num == *temp2.num && temp1.sign == temp2.sign;
}

bool LongNumber::operator!=(const LongNumber &other) const
{
	return !this->operator==(other);
}

bool LongNumber::operator<(const LongNumber &other) const
{
	LongNumber temp1 = *this;
	LongNumber temp2 = other;

	uint16_t MaxFrac = std::max(temp1.FracAccuracy_increased, temp2.FracAccuracy_increased);
	uint16_t MaxInt = std::max(temp1.IntAccuracy_increased, temp2.IntAccuracy_increased);

	temp1.NormalizeDigits(MaxInt, MaxFrac);
	temp2.NormalizeDigits(MaxInt, MaxFrac);

	if (temp1 == temp2)
		return false;
	if (temp1.sign == -1 && temp2.sign == 1)
		return true;
	if (temp1.sign == 1 && temp2.sign == -1)
		return false;

	bool Absolute{false};
	for (size_t i = 0; i < temp1.num->size(); i++)
	{
		if (temp1.num[i] < temp2.num[i])
		{
			Absolute = true;
			break;
		}
		if (temp1.num[i] > temp2.num[i])
			break;
	}

	if (temp1.sign == -1 && temp2.sign == -1)
		return !Absolute;
	return Absolute;
}

bool LongNumber::operator>(const LongNumber &other) const
{
	return *this != other && !(*this < other);
}

LongNumber LongNumber::operator+(const LongNumber &other) const
{
	uint16_t ResIntAcc = std::max(IntAccuracy, other.IntAccuracy);
	uint16_t ResFracAcc = std::max(FracAccuracy, other.FracAccuracy);
	uint16_t ResIntAcc_32 = std::max(IntAccuracy_increased, other.IntAccuracy_increased);
	uint16_t ResFracAcc_32 = std::max(FracAccuracy_increased, other.FracAccuracy_increased);

	LongNumber Res(ResIntAcc, ResFracAcc);

	LongNumber temp1 = *this;
	LongNumber temp2 = other;
	temp1.NormalizeDigits(ResIntAcc_32, ResFracAcc_32);
	temp2.NormalizeDigits(ResIntAcc_32, ResFracAcc_32);

	if (sign == 1 && other.sign == 1)
	{
		SummarizeDeques(*Res.num, *temp1.num, *temp2.num);
		Res.NormalizeAccuracy();
		return Res;
	}
	if (sign == -1 && other.sign == -1){
		Res.sign=-1;
		SummarizeDeques(*Res.num, *temp1.num, *temp2.num);
		Res.NormalizeAccuracy();
		return Res;
	}
	return LongNumber(1, 1);
}

LongNumber operator""_longnum(const char *num)
{
	return LongNumber(num);
}