#include "../include/Longnum.hpp"

#include <iostream>

bool testThatPlusWorks_IntMinimal()
{
	// given
	LongNumber a = 5_longnum;
	LongNumber b = 66_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 71_longnum;
	return (expected == res);
}

bool testThatPlusWorks_BiggerInt()
{
	// given
	LongNumber a = 573828298837389299_longnum;
	LongNumber b = 66189299292919010000011188828_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 66189299293492838298848578127_longnum;
	return (expected == res);
}

bool testThatPlusWorks_FractionalBAse2N()
{
	// given
	LongNumber a = 16617722_longnum;
	LongNumber b = 6611.625_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 1728.625_longnum;
	return (expected == res);
}

bool testThatPlusWorks_FractionalBAseNot2N()
{
	// given
	LongNumber a = 166217.1727_longnum;
	LongNumber b = 661929.625_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 828146.7977_longnum;
	return ((expected - res) < 0.001_longnum);
}

bool testThatPlusWorks_NegativeInt()
{
	// given
	LongNumber a = -16628182_longnum;
	LongNumber b = 66192991_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 49564809_longnum;
	return ((expected - res) < 0.001_longnum);
}

bool testThatPlusWorks_NegativeFractional()
{
	// given
	LongNumber a = 16628182182.199292_longnum;
	LongNumber b = -66192991.1882982_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 16561989191.010994_longnum;
	return ((expected - res) < 0.001_longnum);
}

int main()
{
//
	if (testThatPlusWorks_IntMinimal())
	{
		std::cout << "IntMinimal " << "OK" << std::endl;
	}
	else{
		std::cout << "IntMinimal " << "FAIL" << std::endl;
	}
//
	if (testThatPlusWorks_BiggerInt())
	{
		std::cout << "BiggerInt " << "OK" << std::endl;
	}
	else{
		std::cout << "BiggerInt " << "FAIL" << std::endl;
	}
//
	if (testThatPlusWorks_FractionalBAse2N())
	{
		std::cout << "FractionalBAse2N " << "OK" << std::endl;
	}
	else{
		std::cout << "FractionalBAse2N " << "FAIL" << std::endl;
	}
//
	if (testThatPlusWorks_FractionalBAseNot2N())
	{
		std::cout << "FractionalBAseNot2N " << "OK" << std::endl;
	}
	else{
		std::cout << "FractionalBAseNot2N " << "FAIL" << std::endl;
	}
//
	return 0;
}