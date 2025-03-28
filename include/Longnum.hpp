#pragma once
#ifndef LONGNUM_HPP
#define LONGNUM_HPP

#include <deque>
#include <cinttypes>
#include<string>

class LongNumber
{
private:
	uint16_t IntAccuracy;
	uint16_t FracAccuracy;
	uint16_t IntAccuracy_increased;
	uint16_t FracAccuracy_increased;
	char sign = 1;

	std::deque<unsigned long long> *num;

	void MakeDeque(void *parts);
	void NormalizeDigits(uint16_t IntPart, uint16_t FracPart);
	void NormalizeAccuracy();

public:
	LongNumber();
	LongNumber(uint16_t IntAcc, uint16_t FracAcc);
	LongNumber(long double d);
	LongNumber(long double d, uint16_t IntAcc, uint16_t FracAcc);
	LongNumber(const char *input, uint16_t IntAcc, uint16_t FracAcc);
	LongNumber(const LongNumber &other);
	LongNumber(LongNumber &&other) noexcept;

	~LongNumber();

	LongNumber &operator=(const LongNumber &other);
	LongNumber &operator=(LongNumber &&other);
	LongNumber operator-() const;
	bool operator==(const LongNumber &other) const;
	bool operator!=(const LongNumber &other) const;
	bool operator<(const LongNumber &other) const;
	bool operator>(const LongNumber &other) const;
	bool operator>=(const LongNumber &other) const;
	bool operator<=(const LongNumber &other) const;

	LongNumber operator+(const LongNumber &other) const;
	LongNumber operator-(const LongNumber &other) const;
	LongNumber operator*(const LongNumber &other) const;
	LongNumber operator/(const LongNumber &other) const;

	std::string GetDecimal() const;
};

LongNumber operator""_longnum(const char *num);
LongNumber operator""_longnum(long double d);

LongNumber abs(const LongNumber &num);

class DivisionByZeroError : public std::exception
{
public:
	const char *what() const noexcept;
};

#endif