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
	LongNumber a = LongNumber("573828298837389299",100,1000);
	LongNumber b = LongNumber("66189299292919010000011188828",100,1000);

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = LongNumber("66189299293492838298848578127",100,1000);
	return (expected == res);
}

bool testThatPlusWorks_FractionalBase2N()
{
	// given
	LongNumber a = 16617722_longnum;
	LongNumber b = 6611.625_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = 16624333.625_longnum;
	return (expected == res);
}

bool testThatPlusWorks_FractionalBaseNot2N()
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
	LongNumber a = LongNumber("16628182182.199292",50,1000);
	LongNumber b = -66192991.1882982_longnum;

	// when
	LongNumber res = a + b;

	// then
	LongNumber expected = LongNumber("16561989191.010994",35,1000);
	return ((expected - res) < 0.001_longnum);
}

int main()
{
//
	if (testThatPlusWorks_IntMinimal())
	{
		std::cout << "---IntMinimal--- " << "OK" << std::endl;
	}
	else{
		std::cout << "---IntMinimal--- " << "FAIL" << std::endl;
	}
//
	if (testThatPlusWorks_BiggerInt())
	{
		std::cout << "---BiggerInt--- " << "OK" << std::endl;
	}
	else{
		std::cout << "---BiggerInt--- " << "FAIL" << std::endl;
	}
//
	if (testThatPlusWorks_FractionalBase2N())
	{
		std::cout << "---FractionalBase2N--- " << "OK" << std::endl;
	}
	else{
		std::cout << "---FractionalBase2N--- " << "FAIL" << std::endl;
	}
//
	if (testThatPlusWorks_FractionalBaseNot2N())
	{
		std::cout << "---FractionalBaseNot2N--- " << "OK" << std::endl;
	}
	else{
		std::cout << "---FractionalBaseNot2N--- " << "FAIL" << std::endl;
	}
//
	if(testThatPlusWorks_NegativeInt())
	{
		std::cout << "---NegativeInt--- " << "\tOK" << std::endl;
	}
	else{
		std::cout << "---NegativeInt--- " << "FAIL" << std::endl;
	}
//
	if(testThatPlusWorks_NegativeFractional())
	{
		std::cout << "---NegativeFractional--- " << "OK" << std::endl;
	}
	else{
		std::cout << "---NegativeFractional--- " << "FAIL" << std::endl;
	}
	return 0;
}