#pragma once
#include <random>

class Random
{
public:
	static Random& Instance()
	{
		static Random inst;
		return inst;
	}

	int Range(int one,int two) // range
	{
		gen.seed(rd());
		std::uniform_int_distribution<int> dis(one, two);
		return dis(gen);
	}
	float Range(float one, float two) // range
	{
		gen.seed(rd());
		std::uniform_int_distribution<float> dis(one, two);
		return dis(gen);
	}

private:
	Random() = default;
	~Random() = default;
	Random(const Random&) = delete;
	Random(Random&&) = delete;
	Random operator= (const Random&) = delete;
	Random operator= (Random&&) = delete;

	std::mt19937 gen;
	std::random_device rd;
};