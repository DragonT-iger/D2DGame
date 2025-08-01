#include "pch.h"
#include "Random.h"

int Random::Range(int one, int two)
{
	std::uniform_int_distribution<int> dis(one, two - 1); // 유니티는 이럼
	return dis(*gen);
}

//float Random::Range(float one, float two)
//{
//	std::uniform_real_distribution<float> dis(one, two);
//	return dis(*gen);
//}

Random::Random()
{
	rd = std::make_unique<std::random_device>();
	gen = std::make_unique<std::mt19937>((*rd)());
}
