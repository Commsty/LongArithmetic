#pragma once
#ifndef LONGNUM_HPP
#define LONGNUM_HPP

#include <deque>
#include <cinttypes>

class LongNumber
{
private:
	uint16_t IntAccuracy = 32;
	uint16_t FracAccuracy = 64;
	uint16_t IntAccuracy_increased;
	uint16_t FracAccuracy_increased;
	char sign = 1;

	std::deque<unsigned long long> *num;

	void MakeDeque(void *parts);
	void NormalizeDigits(uint16_t IntPart, uint16_t FracPart);

public:
	LongNumber(uint16_t pref, uint16_t post);
	LongNumber(long double input);
	LongNumber(const char *input);
	LongNumber(const LongNumber &other);
	LongNumber(LongNumber &&other);

	~LongNumber();

	LongNumber &operator=(const LongNumber &other);
	LongNumber &operator=(LongNumber &&other);
	LongNumber operator-() const;
	bool operator==(const LongNumber& other) const;
};

LongNumber operator""_longnum(const char *num);

#endif