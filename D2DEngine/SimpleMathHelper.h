#pragma once


#define M_PI       3.14159265358979323846

namespace MYHelper
{
	constexpr float DegreeToRadian(float deg)
	{
		return static_cast<float>(deg * (M_PI / 180.0f));
	}
	constexpr float RadianToDegree(float rad)
	{
		return static_cast<float>(rad * (180.0f / M_PI));
	}
}