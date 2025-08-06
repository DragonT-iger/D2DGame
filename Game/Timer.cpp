#include "pch.h"
#include <chrono>
#include "Timer.h"

void Timer::Awake()
{
	m_sceneTimer = 0.0f;
}

void Timer::Start()
{

}

void Timer::Update(float deltaTime)
{
	m_sceneTimer += deltaTime;
}
