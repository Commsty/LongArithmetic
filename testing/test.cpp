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

		std::cout
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
		return (abs(expected - res) < 0.000001_longnum);
	}

	bool testThatPlusWorks_LessFractionalBaseNot2N()
	{
		// given
		LongNumber a = LongNumber("709.5489962225", 10, 1000);
		LongNumber b = LongNumber("0.9789632788", 1, 1000);

		// when
		LongNumber res = a + b;

		// then
		LongNumber expected = LongNumber("710.5279595013", 10, 1000);
		return (abs(res - expected) < 0.0000000001_longnum);
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
		return (abs(expected - res) < 0.000001_longnum);
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
		return (abs(expected - res) < 0.000001_longnum);
	}

	bool testThatMinusWorks_IntMinimal()
	{
		// given
		LongNumber a = 581_longnum;
		LongNumber b = 692_longnum;

		// when
		LongNumber res = b - a;

		// then
		LongNumber expected = 111_longnum;
		return (expected == res);
	}

	bool testThatMinusWorks_BiggerInt()
	{
		// given
		LongNumber a = LongNumber("581929929919929299291", 100, 100);
		LongNumber b = LongNumber("6921992929299291", 100, 100);

		// when
		LongNumber res = a - b;

		// then
		LongNumber expected = LongNumber("581923007927000000000", 100, 10);
		return (expected == res);
	}

	bool testThatMinusWorks_FractionalBase2N()
	{
		// given
		LongNumber a = LongNumber("581929929919929299218282882881991.0009765625", 110, 100);
		LongNumber b = LongNumber("218282882881992", 100, 100);

		// when
		LongNumber res = a - b;

		// then
		LongNumber expected = LongNumber("581929929919929298999999999999999.0009765625", 110, 10);
		return (expected == res);
	}

	bool testThatMinusWorks_FractionalBaseNot2N()
	{
		// given
		LongNumber a = 0.1234_longnum;
		LongNumber b = 1.1234_longnum;

		// when
		LongNumber res = a - b;

		// then
		LongNumber expected = -1_longnum;
		return (abs(expected - res) < 0.00001_longnum);
	}

	bool testThatMinusWorks_LessFractionalBaseNot2N()
	{
		// given
		LongNumber a = LongNumber("709.5489962225", 10, 1000);
		LongNumber b = LongNumber("0.9789632788", 1, 1000);

		// when
		LongNumber res = a - b;

		// then
		LongNumber expected = LongNumber("708.5700329437", 10, 1000);
		return (abs(res - expected) < 0.0000000001_longnum);
	}

	bool testThatMinusWorks_NegativeInt()
	{
		// given
		LongNumber a = -16277272_longnum;
		LongNumber b = -188282_longnum;

		// when
		LongNumber res = a - b;

		// then
		LongNumber expected = -16088990_longnum;
		return (expected == res);
	}

	bool testThatMinusWorks_NegativeFractional()
	{
		// given
		LongNumber a = -16277272.123_longnum;
		LongNumber b = 188282.1577_longnum;

		// when
		LongNumber res = a - b;

		// then
		LongNumber expected = -16465554.2807_longnum;
		return (abs(expected - res) < 0.00000000001_longnum);
	}

	bool testThatMultipleWorks_IntMinimal()
	{
		// given
		LongNumber a = 1727_longnum;
		LongNumber b = -188282_longnum;

		// when
		LongNumber res = a * b;

		// then
		LongNumber expected = -325163014_longnum;
		return (expected == res);
	}

	bool testThatMultipleWorks_BiggerInt()
	{
		// given
		LongNumber a = LongNumber("172718288282", 100, 1);
		LongNumber b = LongNumber("-188281882828291912", 100, 1);

		// when
		LongNumber res = a * b;

		// then
		LongNumber expected = LongNumber("-32519724516614667962464975184", 100, 1);
		return (expected == res);
	}

	bool testThatMultipleWorks_FractionalBase2N()
	{
		// given
		LongNumber a = LongNumber("178218818828281.25", 100, 100);
		LongNumber b = LongNumber("4818181", 100, 1);

		// when
		LongNumber res = a * b;

		// then
		LongNumber expected = LongNumber("858690526720866981406.25", 100, 100);
		return (expected == res);
	}

	bool testThatMultipleWorks_FractionalBaseNot2N()
	{
		// given
		LongNumber a = LongNumber("178.2518821928", 20, 1000);
		LongNumber b = LongNumber("491.1882813664", 20, 1000);

		// when
		LongNumber res = a * b;

		// then
		LongNumber expected = LongNumber("87555.235664607", 100, 1000);
		return (abs(res - expected) < 0.000000001_longnum);
	}

	bool testThatMultipleWorks_LessFractionalBaseNot2N()
	{
		// given
		LongNumber a = LongNumber("709.5489962225", 10, 1000);
		LongNumber b = LongNumber("0.9789632788", 1, 1000);

		// when
		LongNumber res = a * b;

		// then
		LongNumber expected = LongNumber("694.6224118112", 10, 1000);
		return (abs(res - expected) < 0.0000000001_longnum);
	}

	bool testThatDivideWorks_IntMinimal()
	{
		// given
		LongNumber a = 1992928_longnum;
		LongNumber b = 784_longnum;

		// when
		LongNumber res = a / b;

		// then
		LongNumber expected = 2542_longnum;
		return (expected == res);
	}

	bool testThatDivideWorks_BiggerInt()
	{
		// given
		LongNumber a = LongNumber("182873883421990",100,1000);
		LongNumber b = 1030_longnum;

		// when
		LongNumber res = a / b;

		// then
		LongNumber expected = LongNumber("177547459633",100,1000);
		return (expected == res);
	}

	bool testThatDivideWorks_FractionalFirst()
	{
		// given
		LongNumber a = LongNumber("181892892911772.781882", 100, 1000);
		LongNumber b = LongNumber("178738.1881382", 100, 1000);

		// when
		LongNumber res = a / b;

		// then
		LongNumber expected = LongNumber("1017649864.34311156", 100, 1000);
		return (abs(res - expected) < 0.00000001_longnum);
	}

	bool testThatDivideWorks_FractionalSecond()
	{
		// given
		LongNumber a = LongNumber("181892892911772.781882", 100, 1000);
		LongNumber b = LongNumber("0.000002", 100, 1000);

		// when
		LongNumber res = a / b;

		// then
		LongNumber expected = LongNumber("90946446455886390941", 100, 1000);
		return (abs(res - expected) < 0.00000001_longnum);
	}

	bool testThatDivideWorks_FractionalThird()//check
	{
		// given
		LongNumber a = LongNumber("5.1626727717211828", 10, 3000);
		LongNumber b = LongNumber("3.177278838383", 10, 3000);

		// when
		LongNumber res = a / b;

		// then
		LongNumber expected = LongNumber("1.6248724252192487806", 10, 3000);
		return (abs(res - expected) < LongNumber("0.0000000000000000001",1,3000));
	}
}

int main()
{
	std::vector<Test> MyTests;
	//
	if (testThatPlusWorks_IntMinimal())
	{
		MyTests.push_back({"testThatPlusWorks_IntMinimal", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_IntMinimal", false});
	}
	//
	if (testThatPlusWorks_BiggerInt())
	{
		MyTests.push_back({"testThatPlusWorks_BiggerInt", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_BiggerInt", false});
	}
	//
	if (testThatPlusWorks_FractionalBase2N())
	{
		MyTests.push_back({"testThatPlusWorks_FractionalBase2N", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_FractionalBase2N", false});
	}
	//
	if (testThatPlusWorks_FractionalBaseNot2N())
	{
		MyTests.push_back({"testThatPlusWorks_FractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_FractionalBaseNot2N", false});
	}
	//
	if (testThatPlusWorks_LessFractionalBaseNot2N())
	{
		MyTests.push_back({"testThatPlusWorks_LessFractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_LessFractionalBaseNot2N", false});
	}
	//
	if (testThatPlusWorks_NegativeInt())
	{
		MyTests.push_back({"testThatPlusWorks_NegativeInt", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_NegativeInt", false});
	}
	//
	if (testThatPlusWorks_NegativeFractional())
	{
		MyTests.push_back({"testThatPlusWorks_NegativeFractional", true});
	}
	else
	{
		MyTests.push_back({"testThatPlusWorks_NegativeFractional", false});
	}
	//
	if (testThatMinusWorks_IntMinimal())
	{
		MyTests.push_back({"testThatMinusWorks_IntMinimal", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_IntMinimal", false});
	}
	//
	if (testThatMinusWorks_BiggerInt())
	{
		MyTests.push_back({"testThatMinusWorks_BiggerInt", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_BiggerInt", false});
	}
	//
	if (testThatMinusWorks_FractionalBase2N())
	{
		MyTests.push_back({"testThatMinusWorks_FractionalBase2N", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_FractionalBase2N", false});
	}
	//
	if (testThatMinusWorks_FractionalBaseNot2N())
	{
		MyTests.push_back({"testThatMinusWorks_FractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_FractionalBaseNot2N", false});
	}
	//
	if (testThatMinusWorks_LessFractionalBaseNot2N())
	{
		MyTests.push_back({"testThatMinusWorks_LessFractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_LessFractionalBaseNot2N", false});
	}
	//
	if (testThatMinusWorks_NegativeInt())
	{
		MyTests.push_back({"testThatMinusWorks_NegativeInt", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_NegativeInt", false});
	}
	//
	if (testThatMinusWorks_NegativeFractional())
	{
		MyTests.push_back({"testThatMinusWorks_NegativeFractional", true});
	}
	else
	{
		MyTests.push_back({"testThatMinusWorks_NegativeFractional", false});
	}
	//
	if (testThatMultipleWorks_IntMinimal())
	{
		MyTests.push_back({"testThatMultipleWorks_IntMinimal", true});
	}
	else
	{
		MyTests.push_back({"testThatMultipleWorks_IntMinimal", false});
	}
	//
	if (testThatMultipleWorks_BiggerInt())
	{
		MyTests.push_back({"testThatMultipleWorks_BiggerInt", true});
	}
	else
	{
		MyTests.push_back({"testThatMultipleWorks_BiggerInt", false});
	}
	//
	if (testThatMultipleWorks_FractionalBase2N())
	{
		MyTests.push_back({"testThatMultipleWorks_FractionalBase2N", true});
	}
	else
	{
		MyTests.push_back({"testThatMultipleWorks_FractionalBase2N", false});
	}
	//
	if (testThatMultipleWorks_FractionalBaseNot2N())
	{
		MyTests.push_back({"testThatMultipleWorks_FractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"testThatMultipleWorks_FractionalBaseNot2N", false});
	}
	//
	if (testThatMultipleWorks_LessFractionalBaseNot2N())
	{
		MyTests.push_back({"testThatMultipleWorks_LessFractionalBaseNot2N", true});
	}
	else
	{
		MyTests.push_back({"testThatMultipleWorks_LessFractionalBaseNot2N", false});
	}
	//
	if (testThatDivideWorks_IntMinimal())
	{
		MyTests.push_back({"testThatDivideWorks_IntMinimal", true});
	}
	else
	{
		MyTests.push_back({"testThatDivideWorks_IntMinimal", false});
	}
	//
	if (testThatDivideWorks_BiggerInt())
	{
		MyTests.push_back({"testThatDivideWorks_BiggerInt", true});
	}
	else
	{
		MyTests.push_back({"testThatDivideWorks_BiggerInt", false});
	}
	//
	if (testThatDivideWorks_FractionalFirst())
	{
		MyTests.push_back({"testThatDivideWorks_FractionalFirst", true});
	}
	else
	{
		MyTests.push_back({"testThatDivideWorks_FractionalFirst", false});
	}
	//
	if (testThatDivideWorks_FractionalSecond())
	{
		MyTests.push_back({"testThatDivideWorks_FractionalSecond", true});
	}
	else
	{
		MyTests.push_back({"testThatDivideWorks_FractionalSecond", false});
	}
	//
	if (testThatDivideWorks_FractionalThird())
	{
		MyTests.push_back({"testThatDivideWorks_FractionalThird", true});
	}
	else
	{
		MyTests.push_back({"testThatDivideWorks_FractionalThird", false});
	}
	//

	PrintResults(MyTests);
	return 0;
}