#pragma once
#ifndef LNUM_UTILS_HPP
#define LNUM_UTILS_HPP


#include<string>
#include<memory>
#include<deque>


struct LongNumParts{
    std::string IntPart;
    std::string FracPart;
};

bool IsZeroDeq(const std::deque<unsigned long long>* DeqPtr);

std::unique_ptr<LongNumParts> DecToBinary(const std::string &dec, int bin_precision_int, int bin_precision_frac);

std::string MakeString(const long double &a);

std::deque<unsigned long long>* PushToDeque(const std::string &Bin);

#endif