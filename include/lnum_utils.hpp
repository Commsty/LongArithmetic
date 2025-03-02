#pragma once
#ifndef LNUM_UTILS_HPP
#define LNUM_UTILS_HPP

#include <string>
#include <deque>

struct LongNumParts
{
	std::string IntPart;
	std::string FracPart;
};

bool IsZeroDeq(const std::deque<unsigned long long> *DeqPtr);

void SummarizeDeques(std::deque<unsigned long long> &res,
					 const std::deque<unsigned long long> &s1, const std::deque<unsigned long long> &s2);

void SubstractDeques(std::deque<unsigned long long> &res,
					 std::deque<unsigned long long> &s1, const std::deque<unsigned long long> &s2);

void MultiplyDeques(std::deque<unsigned long long> &res,
					const std::deque<unsigned long long> &s1, const std::deque<unsigned long long> &s2);

void shift_deque(std::deque<unsigned long long> &shifted_deq, int bits);

LongNumParts *DecToBinary(const std::string &dec, int bin_precision_int, int bin_precision_frac);

std::string MakeString(const long double &a);

std::deque<unsigned long long> *PushToDeque(const std::string &Bin);

#endif