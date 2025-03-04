#include "../include/Longnum.hpp"

#include <iostream>
#include <chrono>
#include <ostream>

class TimerGuard
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> start;
	const std::string name;
	std::ostream &output;

public:
	TimerGuard() = delete;

	TimerGuard(std::string process_name, std::ostream &stream = std::cout)
		: 
		  start(std::chrono::high_resolution_clock::now()),
		  name(process_name),
		  output(stream)

	{
	}

	~TimerGuard()
	{
		const auto end = std::chrono::high_resolution_clock::now();
		const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
								  end - start)
								  .count();

		output << name << " " << duration << "ms."<< std::endl;
	}
};

const LongNumber c1("262537412640768000", 1000, 384);
const LongNumber c2("512384047.99600074981255466992791529927985060803010899361005608614623126188949113059562159893746802321614885", 1000, 384);

LongNumber pow(const LongNumber &a, unsigned power)
{
	LongNumber res("1", 1000, 384);
	for (size_t i = 0; i < power; i++)
		res = res * a;
	return res;
}

LongNumber factorial(LongNumber a)
{
	if (a == 0_longnum)
		return LongNumber(1, 1100, 384);
	return a * factorial(a - 1_longnum);
}

int main()
{
	TimerGuard Pi = TimerGuard("Pi has been calculated.", std::cout);
	LongNumber Opposite(1000, 384);
	LongNumber upper(1000, 384), lower(1000, 384);

	const int iters = 100 / 14 + 2;
	for (int i = 0; i < iters; i++)
	{
		upper = factorial(6_longnum * LongNumber(i, 1000, 384)) * (545140134_longnum * LongNumber(i, 1000, 384) + 13591409_longnum);

		lower = factorial(3_longnum * LongNumber(i, 1000, 384)) * pow(factorial(LongNumber(i, 1000, 384)), 3);
		lower = lower * pow(c1, i) * c2;

		if (i % 2 == 0)
		{
			Opposite = Opposite + (upper / lower);
			continue;
		}
		Opposite = Opposite - (upper / lower);
	}

	LongNumber pi = LongNumber(1, 10, 384) / (LongNumber(12, 10, 384) * Opposite);

	std::cout << pi.GetDecimal().substr(0, 102) << std::endl;

	return 0;
}
