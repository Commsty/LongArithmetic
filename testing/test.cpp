#include "../include/Longnum.hpp"
#include <iostream>
#include <vector>
#include <iomanip>

namespace
{
	struct Test
	{
		std::string TestName;
		bool verdict;
	};

	void PrintResults(const std::vector<Test> &Tests)
	{
		size_t MaxLen_TestName = 0;
		for (const auto &test : Tests)
			MaxLen_TestName = std::max(MaxLen_TestName, test.TestName.length());

		std::cout << "\n"
				  << std::left << std::setw((int)MaxLen_TestName) << "Test Name" << "  Verdict";
		std::cout << std::setfill('-') << std::setw((int)MaxLen_TestName + 10) << "\n"
				  << std::setfill(' ');
		std::cout << std::endl;

		for (const auto &test : Tests)
		{
			std::cout << std::left << std::setw((int)MaxLen_TestName) << test.TestName << "  "
					  << (test.verdict ? "\033[32mOK\033[0m" : "\033[31mFAIL\033[0m") << "\n";
		}
	}

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
		LongNumber a = LongNumber("573828298837389299", 100, 1000);
		LongNumber b = LongNumber("66189299292919010000011188828", 100, 1000);

		// when
		LongNumber res = a + b;

		// then
		LongNumber expected = LongNumber("66189299293492838298848578127", 100, 1000);
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
		LongNumber a = LongNumber("16628182182.199292", 50, 1000);
		LongNumber b = -66192991.1882982_longnum;

		// when
		LongNumber res = a + b;

		// then
		LongNumber expected = LongNumber("16561989191.010994", 35, 1000);
		return ((expected - res) < 0.001_longnum);
	}
}

int main()
{
	std::vector<Test> MyTests;
	//
	if (testThatPlusWorks_IntMinimal())
	{
		MyTests.push_back({"IntMinimal", true});
	}
	else
	{
		MyTests.push_back({"IntMinimal", false});
	}
	//
	if (testThatPlusWorks_BiggerInt())
	{
		MyTests.push_back({"BiggerInt", true});
	}
	else
	{
		MyTests.push_back({"BiggerInt", false});
	}
	//
	if (testThatPlusWorks_FractionalBase2N())
	{
		MyTests.push_back({"FractionalBase2N", true});
	}
	else
	{
		MyTests.push_back({"FractionalBase2N", false});
	}
	//
	if (testThatPlusWorks_FractionalBaseNot2N())
	{
		MyTests.push_back({"FractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"FractionalBaseNot2N", false});
	}
	//
	if (testThatPlusWorks_NegativeInt())
	{
		MyTests.push_back({"NegativeInt", true});
	}
	else
	{
		MyTests.push_back({"NegativeInt", false});
	}
	//
	if (testThatPlusWorks_NegativeFractional())
	{
		MyTests.push_back({"NegativeFractional", true});
	}
	else
	{
		MyTests.push_back({"NegativeFractional", false});
	}
	//


	
	PrintResults(MyTests);
	return 0;
}