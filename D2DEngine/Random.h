#pragma once
#include <random>

class Random
{
public:
	int operator()(int one, int two) // range
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(one, two);
		return dis(gen);
	}

	float operator()(float one, float two) // range
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<float> dis(one, two);
		return dis(gen);
	}
};
