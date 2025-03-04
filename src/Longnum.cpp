#include "../include/Longnum.hpp"
#include "../include/lnum_utils.hpp"

#include <iostream>

const char *DivisionByZeroError::what() const noexcept
{
	return "Division by zero is not allowed!";
}

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
			std::cout << "Warning: IntAccuracy has been increased up to " + std::to_string(new_acc) + " binary digits."
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

LongNumber::LongNumber(long double d) : IntAccuracy(64),
										FracAccuracy(64)
{
	const std::string str_num = MakeString(d);
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

LongNumber::LongNumber(long double d, uint16_t IntAcc, uint16_t FracAcc) : IntAccuracy(IntAcc),
																		   FracAccuracy(FracAcc)
{
	std::string str_num = MakeString(d);

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

LongNumber::LongNumber(const char *input, uint16_t IntAcc = 32, uint16_t FracAcc = 64) : IntAccuracy(IntAcc),
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
		if ((*temp1.num)[i] < (*temp2.num)[i])
		{
			Absolute = true;
			break;
		}
		if ((*temp1.num)[i] > (*temp2.num)[i])
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

bool LongNumber::operator>=(const LongNumber &other) const
{
	return *this == other || *this > other;
}

bool LongNumber::operator<=(const LongNumber &other) const
{
	return *this == other || *this < other;
}

LongNumber LongNumber::operator+(const LongNumber &other) const
{
	if (sign == 1 && other.sign == -1)
		return *this - (-other);
	if (sign == -1 && other.sign == 1)
		return other - (-*this);

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
	else
	{
		Res.sign = -1;
		SummarizeDeques(*Res.num, *temp1.num, *temp2.num);
		Res.NormalizeAccuracy();
		return Res;
	}
}

LongNumber LongNumber::operator-(const LongNumber &other) const
{
	if (sign == 1 && other.sign == -1)
		return *this + (-other);
	if (sign == -1 && other.sign == 1)
		return *this + (-other);

	uint16_t ResIntAcc = std::max(IntAccuracy, other.IntAccuracy);
	uint16_t ResFracAcc = std::max(FracAccuracy, other.FracAccuracy);
	uint16_t ResIntAcc_32 = std::max(IntAccuracy_increased, other.IntAccuracy_increased);
	uint16_t ResFracAcc_32 = std::max(FracAccuracy_increased, other.FracAccuracy_increased);

	LongNumber Res(ResIntAcc, ResFracAcc);

	LongNumber temp1 = *this;
	LongNumber temp2 = other;
	temp1.NormalizeDigits(ResIntAcc_32, ResFracAcc_32);
	temp2.NormalizeDigits(ResIntAcc_32, ResFracAcc_32);

	if (other == *this)
		return Res;

	if (sign == 1 && other.sign == 1)
	{
		if (*this > other)
		{
			SubstractDeques(*Res.num, *temp1.num, *temp2.num);
			Res.NormalizeAccuracy();
			return Res;
		}
		else
		{
			SubstractDeques(*Res.num, *temp2.num, *temp1.num);
			Res.NormalizeAccuracy();
			Res.sign = -1;
			return Res;
		}
	}
	if (*this > other)
	{
		SubstractDeques(*Res.num, *temp2.num, *temp1.num);
		Res.NormalizeAccuracy();
		return Res;
	}
	else
	{
		SubstractDeques(*Res.num, *temp1.num, *temp2.num);
		Res.NormalizeAccuracy();
		Res.sign = -1;
		return Res;
	}
}

LongNumber LongNumber::operator*(const LongNumber &other) const
{
	LongNumber Res("0", 1, 0);
	Res.sign = other.sign * sign;

	MultiplyDeques(*Res.num, *num, *other.num);

	uint16_t ResFracAcc_32 = other.FracAccuracy_increased + FracAccuracy_increased;
	while (ResFracAcc_32 > std::max(other.FracAccuracy_increased, FracAccuracy_increased))
	{
		ResFracAcc_32--;
		Res.num->pop_back();
	}
	Res.FracAccuracy_increased = ResFracAcc_32;
	Res.FracAccuracy = std::max(FracAccuracy, other.FracAccuracy);

	uint16_t ResIntAcc_32 = (uint16_t)Res.num->size() - ResFracAcc_32;
	while (ResIntAcc_32 > std::max(other.IntAccuracy_increased, IntAccuracy_increased) &&
		   Res.num->front() == 0ull)
	{
		Res.num->pop_front();
		ResIntAcc_32--;
	}

	Res.IntAccuracy_increased = ResIntAcc_32;
	if (Res.num->front() == 0)
		Res.IntAccuracy = std::max(other.IntAccuracy, IntAccuracy);
	else
	{
		unsigned new_acc = (Res.IntAccuracy_increased - 1) * 32u;
		new_acc += static_cast<unsigned>(64 - __builtin_clzll(Res.num->front()));
		Res.IntAccuracy = static_cast<uint16_t>(new_acc);
	}

	if (Res.IntAccuracy > std::max(other.IntAccuracy, IntAccuracy))
		std::cout << "Warning: IntAccuracy has been increased up to " << std::to_string(Res.IntAccuracy) << " binary digits.\n";

	return Res;
}

LongNumber LongNumber::operator/(const LongNumber &other) const
{
	if (IsZeroDeq(other.num))
		throw DivisionByZeroError();

	uint16_t TotalFracAcc = std::max(other.FracAccuracy_increased, FracAccuracy_increased);
	uint16_t ToAddDividend = TotalFracAcc - FracAccuracy_increased;
	uint16_t ToAddDivider = TotalFracAcc - other.FracAccuracy_increased;

	LongNumber dividend = abs(*this);
	LongNumber divider = abs(other);

	dividend.num->insert(dividend.num->end(), ToAddDividend, 0ull);
	divider.num->insert(divider.num->end(), ToAddDivider, 0ull);

	while (dividend.num->front() == 0ull)
		dividend.num->pop_front();
	while (divider.num->front() == 0ull)
		divider.num->pop_front();

	dividend.IntAccuracy_increased = (uint16_t)dividend.num->size();
	divider.IntAccuracy_increased = (uint16_t)divider.num->size();

	dividend.IntAccuracy = (uint16_t)dividend.IntAccuracy_increased * 32u;
	divider.IntAccuracy = (uint16_t)divider.IntAccuracy_increased * 32u;

	dividend.FracAccuracy_increased = divider.FracAccuracy_increased = 0;
	dividend.FracAccuracy = divider.FracAccuracy = 0;

	LongNumber res, multiplied, newDividend;
	int res_size = static_cast<int>(dividend.IntAccuracy_increased) - static_cast<int>(divider.IntAccuracy_increased) + 1;

	res_size >= 1 ? res.num->resize(res_size) : res.num->resize(1);
	int bitToCheck = res_size * 32 - 1;
	while (dividend >= divider && bitToCheck >= 0)
	{
		multiplied = divider;
		shift_deque(*multiplied.num, bitToCheck);
		multiplied.IntAccuracy_increased = (uint16_t)multiplied.num->size();
		multiplied.IntAccuracy = (uint16_t)(multiplied.IntAccuracy_increased * 32u);

		newDividend = dividend - multiplied;

		if (newDividend >= 0_longnum)
		{
			dividend = newDividend;
			(*res.num)[res_size - bitToCheck / 32 - 1] |= (1ull << bitToCheck % 32);
		}
		bitToCheck--;
	}
	while (res.num->front() == 0ull && res.num->size() > 1)
		res.num->pop_front();
	while (res.num->size() < std::max(IntAccuracy_increased, other.IntAccuracy_increased))
		res.num->push_front(0ull);
	res.IntAccuracy_increased = (uint16_t)res.num->size();

	if (res.num->front() == 0)
		res.IntAccuracy = std::max(other.IntAccuracy, IntAccuracy);
	else
	{
		unsigned new_acc = (res.IntAccuracy_increased - 1) * 32u;
		new_acc += static_cast<unsigned>(64 - __builtin_clzll(res.num->front()));
		res.IntAccuracy = static_cast<uint16_t>(new_acc);
	}

	if (res.IntAccuracy > std::max(IntAccuracy, other.IntAccuracy))
		std::cout << "Warning: IntAccuracy has been increased up to " << std::to_string(res.IntAccuracy) << " binary digits.\n";

	int resFracAcc_32 = static_cast<int>(std::max(FracAccuracy_increased, other.FracAccuracy_increased));

	while (resFracAcc_32-- > 0)
	{
		dividend.num->push_back(0ull);
		dividend.IntAccuracy_increased++;
		dividend.IntAccuracy += 32;

		if (dividend < divider)
		{
			res.num->push_back(0ull);
			continue;
		}
		else
		{
			bitToCheck = 31;
			unsigned long long resBlock = 0ull;
			while (dividend >= divider && bitToCheck >= 0)
			{
				multiplied = divider;
				shift_deque(*multiplied.num, bitToCheck);
				multiplied.IntAccuracy_increased = (uint16_t)multiplied.num->size();
				multiplied.IntAccuracy = (uint16_t)(multiplied.IntAccuracy_increased * 32u);

				newDividend = dividend - multiplied;

				if (newDividend >= 0_longnum)
				{
					dividend = newDividend;
					resBlock |= (1ull << bitToCheck % 32);
				}
				bitToCheck--;
			}
			res.num->push_back(resBlock);
		}
	}
	res.FracAccuracy_increased = std::max(FracAccuracy_increased, other.FracAccuracy_increased);
	res.FracAccuracy = (uint16_t)res.FracAccuracy_increased * 32u;
	res.sign = sign * other.sign;
	return res;
}

std::string LongNumber::GetDecimal() const
{
	auto cpy_deq = *num;
	if (sign == 1)
		return Transfer(cpy_deq, IntAccuracy_increased, FracAccuracy_increased);
	return "-" + Transfer(*num, IntAccuracy_increased, FracAccuracy_increased);
}

LongNumber operator""_longnum(const char *num)
{
	return LongNumber(num);
}

LongNumber operator""_longnum(long double d)
{
	return LongNumber(d, 64, 64);
}

LongNumber abs(const LongNumber &num)
{
	if (num < 0_longnum)
		return -num;
	return num;
}