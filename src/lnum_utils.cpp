#include "../include/lnum_utils.hpp"

#include <algorithm>
#include<sstream>
#include<iomanip>


namespace {
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


std::unique_ptr<LongNumParts> DecToBinary(const std::string &dec, int bin_precision_int, int bin_precision_frac)
{
    size_t DotPos = dec.find('.');
    std::string IntPart = DotPos != dec.npos ? dec.substr(0, DotPos) : dec;
    std::string FracPart = DotPos != dec.npos ? dec.substr(DotPos + 1) : "0";

    auto data = std::make_unique<LongNumParts>(LongNumParts());

    data->IntPart = IntToBin(IntPart, bin_precision_int);
    data->FracPart = FracToBin(FracPart, bin_precision_frac);

    return data;
}


std::string MakeString(const long double &a)
{
    std::ostringstream lf_stream;
    lf_stream << std::setprecision(15) << a;
    return lf_stream.str();
}


std::deque<unsigned long long>* PushToDeque(const std::string &Bin)
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