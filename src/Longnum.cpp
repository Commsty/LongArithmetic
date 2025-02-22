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
}

LongNumber::LongNumber(uint16_t pref, uint16_t post) : IntAccuracy(pref), FracAccuracy(post)
{
	const std::string str_num = "0";
	std::unique_ptr<LongNumParts> my_num_parts = DecToBinary(str_num, (int)IntAccuracy, (int)FracAccuracy);

	uint16_t act_int_accuracy = (uint16_t)((my_num_parts->IntPart).length() - (my_num_parts->IntPart).find_first_not_of('0'));

	if (IntAccuracy < act_int_accuracy && act_int_accuracy < (my_num_parts->IntPart).length())
	{
		IntAccuracy = act_int_accuracy;
		std::cout << "Warning: IntAccuracy has been increased up to " + std::to_string(act_int_accuracy) + " binary digits."
				  << std::endl;
	}

	MakeDeque(my_num_parts.get());
}

LongNumber::LongNumber(long double input)
{
	const std::string str_num = MakeString(input);
	std::unique_ptr<LongNumParts> my_num_parts = DecToBinary(str_num, (int)IntAccuracy, (int)FracAccuracy);

	uint16_t act_int_accuracy = (uint16_t)((my_num_parts->IntPart).length() - (my_num_parts->IntPart).find_first_not_of('0'));

	if (IntAccuracy < act_int_accuracy && act_int_accuracy < (my_num_parts->IntPart).length())
	{
		IntAccuracy = act_int_accuracy;
		std::cout << "Warning: IntAccuracy has been increased up to " + std::to_string(act_int_accuracy) + " binary digits."
				  << std::endl;
	}

	MakeDeque(my_num_parts.get());
}

LongNumber::LongNumber(const char *input)
{
	const std::string str_num = std::string(input);

	std::unique_ptr<LongNumParts> my_num_parts = DecToBinary(str_num, (int)IntAccuracy, (int)FracAccuracy);

	uint16_t act_int_accuracy = (uint16_t)((my_num_parts->IntPart).length() - (my_num_parts->IntPart).find_first_not_of('0'));

	if (IntAccuracy < act_int_accuracy && act_int_accuracy < (my_num_parts->IntPart).length())
	{
		IntAccuracy = act_int_accuracy;
		std::cout << "Warning: IntAccuracy has been increased up to " + std::to_string(act_int_accuracy) + " binary digits."
				  << std::endl;
	}

	MakeDeque(my_num_parts.get());
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

LongNumber::LongNumber(LongNumber &&other) :

											 IntAccuracy(other.IntAccuracy),
											 FracAccuracy(other.FracAccuracy),
											 IntAccuracy_increased(other.IntAccuracy_increased),
											 FracAccuracy_increased(other.FracAccuracy_increased),
											 sign(other.sign)
{
	num = other.num;
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

LongNumber operator""_longnum(const char *num)
{
	return LongNumber(num);
}