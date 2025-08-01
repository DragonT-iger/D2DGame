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

	int Range(int one, int two);
	//float Range(float one, float two);

private:
	Random();
	~Random() = default;
	Random(const Random&) = delete;
	Random(Random&&) = delete;
	Random operator= (const Random&) = delete;
	Random operator= (Random&&) = delete;

	std::unique_ptr<std::mt19937> gen;
	std::unique_ptr<std::random_device> rd;
};