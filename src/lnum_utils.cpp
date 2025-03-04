#include "../include/lnum_utils.hpp"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include <limits>

namespace
{
	std::string DivideByTwo(const std::string &Dividend)
	{
		int Overload = 0;
		std::string res = "";
		for (char ch_digit : Dividend)
		{
			int digit = (ch_digit - '0') + Overload * 10;
			res.push_back((char)(digit / 2) + '0');
			Overload = digit % 2;
		}
		res.erase(0, res.find_first_not_of('0'));
		return res;
	}

	std::string MultipleByTwo(const std::string &Factor)
	{
		std::string res = "";
		int Overload = 0;
		for (auto ch = Factor.rbegin(); ch != Factor.rend(); ch++)
		{
			int digit = (*ch - '0') * 2 + Overload;
			res.push_back((char)(digit % 10) + '0');
			Overload = digit / 10;
		}
		if (Overload != 0)
			res.push_back((char)Overload + '0');
		std::reverse(res.begin(), res.end());

		return res;
	}

	std::string IntToBin(std::string integer, int precision)
	{
		std::string res = "";
		while (!integer.empty())
		{
			int digit = (int)(integer.back() + '0') % 2;
			res.push_back((char)digit + '0');
			integer = DivideByTwo(integer);
		}
		std::reverse(res.begin(), res.end());

		if ((int)res.length() <= precision)
		{
			int cnt_digits = precision - (int)res.length();
			std::string new_res = "";
			new_res.append(cnt_digits, '0');
			new_res.append((32 - precision % 32) % 32, '0');
			new_res.append(res);
			return new_res;
		}

		else
		{
			int cnt_digits = (32 - (int)res.length() % 32) % 32;
			std::string new_res = "";
			new_res.append(cnt_digits, '0');
			new_res.append(res);
			return new_res;
		}
	}

	std::string FracToBin(std::string frac, int precision)
	{
		std::string res = "";
		int precision_copy = precision;
		while (precision-- > 0 && !frac.empty())
		{
			size_t prev_len = frac.length();
			frac = MultipleByTwo(frac);
			prev_len == frac.length() ? res.push_back('0') : res.push_back('1');
			if (prev_len != frac.length())
				frac.erase(0, 1);
			if (frac.back() == '0')
				frac.pop_back();
		}

		if ((int)res.length() < precision_copy)
			res.append(precision_copy - res.length(), '0');

		int cnt_digits = (32 - precision_copy % 32) % 32;
		res.append(cnt_digits, '0');

		return res;
	}

	unsigned long long PushToULL(const std::string &BinNum)
	{
		unsigned long long res = 0;
		for (char bit : BinNum)
		{
			res = (res << 1) | (bit - '0');
		}

		return res;
	}
}

bool IsZeroDeq(const std::deque<unsigned long long> *DeqPtr)
{
	for (auto it = DeqPtr->begin(); it != DeqPtr->end(); it++)
		if (*it != 0ull)
			return false;
	return true;
}

void SummarizeDeques(std::deque<unsigned long long> &res,
					 const std::deque<unsigned long long> &s1, const std::deque<unsigned long long> &s2)
{
	unsigned long long mask = ~0xFFFFFFFFull;
	for (long long i = (long long)(res.size() - 1ull); i >= 0; i--)
	{
		res[i] += (s1[i] + s2[i]);

		if ((res[i] & mask) != 0 && i != 0ull)
			res[i - 1] += 1;

		if ((res[i] & mask) != 0 && i == 0ull)
		{
			res[i] = res[i] & 0xFFFFFFFFull;
			res.push_front(1ull);
			break;
		}

		res[i] = res[i] & 0xFFFFFFFFull;
	}
}

void SubstractDeques(std::deque<unsigned long long> &res,
					 std::deque<unsigned long long> &s1, const std::deque<unsigned long long> &s2)
{
	long long i = s1.size() - 1;

	while (i >= 0)
	{
		long long diff = (long long)(s1[i] - s2[i]);
		if (diff < 0ll)
		{
			long long j = i - 1;
			while (j >= 0 && s1[j] == 0)
				j--;
			s1[j++]--;
			while (j != i)
				s1[j++] += 0xFFFFFFFF;
			s1[j] += 0x100000000ull;
			diff = s1[i] - s2[i];
		}
		res[i] = diff;
		i--;
	}
}

void MultiplyDeques(std::deque<unsigned long long> &res,
					const std::deque<unsigned long long> &s1, const std::deque<unsigned long long> &s2)
{
	res.resize(s2.size() + s1.size());
	long long down_numpos = s2.size() - 1, upper_numpos;
	long long shift = 0;
	unsigned long long mask = ~0xFFFFFFFFull;
	while (down_numpos >= 0)
	{
		upper_numpos = s1.size() - 1;
		unsigned long long multiplier = s2[down_numpos--];
		long long write_pos = res.size() - 1 - shift;
		while (upper_numpos >= 0)
		{
			res[write_pos] += (multiplier * s1[upper_numpos--]);
			size_t carry = write_pos;
			while ((res[carry] & mask) != 0)
			{
				res[carry - 1] += (res[carry] / (0x100000000ull));
				res[carry] %= (0x100000000ull);
				carry--;
			}
			write_pos--;
		}
		shift++;
	}
}

void shift_deque(std::deque<unsigned long long> &shifted_deq, int bits)
{
	shifted_deq.insert(shifted_deq.end(), bits / 32u, 0ull);

	bits %= 32u;
	unsigned long long mask = 0xFFFFFFFFull, carry = 0ull;
	for (long long i = shifted_deq.size() - 1; i >= 0; i--)
	{
		shifted_deq[i] = (shifted_deq[i] << bits) | carry;
		carry = shifted_deq[i] >> 32;
		shifted_deq[i] &= mask;
	}

	if (carry != 0ull)
		shifted_deq.push_front(carry);
}

LongNumParts *DecToBinary(const std::string &dec, int bin_precision_int, int bin_precision_frac)
{
	size_t DotPos = dec.find('.');
	std::string IntPart = DotPos != dec.npos ? dec.substr(0, DotPos) : dec;
	std::string FracPart = DotPos != dec.npos ? dec.substr(DotPos + 1) : "0";

	LongNumParts *data = new LongNumParts;

	data->IntPart = IntToBin(IntPart, bin_precision_int);
	data->FracPart = FracToBin(FracPart, bin_precision_frac);

	return data;
}

std::string Transfer(std::deque<unsigned long long> deq, unsigned IntNumber, unsigned FracNumber)
{
	std::string resInt = "0";
	int power = 0;
	for (long long i = IntNumber - 1; i >= 0; i--)
	{
		std::string temp = std::to_string(deq[i]);
		for (int j = 0; j < power; j++)
			temp = MultipleByTwo(temp);
		// resInt = SummarizeStringsInteger(temp, resInt);
		power += 32;
	}

	std::string resFrac = "0";
	std::string frac = "5";
	for (long long i = IntNumber; i < IntNumber + FracNumber; i++)
	{
		// std::string temp = GetBinary(deq[i]);
		for (int j = 0; j < 32; j++)
		{
			// i > IntNumber || j > 0 ? frac = DivideByTwoFractional(frac) : frac = frac;
			// if (temp[j] == '1')
				// resFrac = SummarizeStringsFractional(resFrac, frac);
		}
	}
	return resInt + '.' + resFrac;
}


std::string MakeString(const long double &a)
{
	std::ostringstream lf_stream;
	lf_stream << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10) << a;
	return lf_stream.str();
}

std::deque<unsigned long long> *PushToDeque(const std::string &Bin)
{
	auto dq_ptr = new std::deque<unsigned long long>;

	for (size_t i = 0; i < Bin.length(); i += 32)
	{
		const std::string BinPart = Bin.substr(i, 32);
		unsigned long long digit = PushToULL(BinPart);
		dq_ptr->push_back(digit);
	}

	return dq_ptr;
}