#include "pch.h"
#include "UITest.h"

void UITest::Awake()
{
	m_value = 1.0f;
}

void UITest::Start()
{
	m_SlideBar = GetComponent<Slide_Bar>();
}

void UITest::Update(float dt)
{
	if (Input.GetKeyPressed(Keycode::LEFT))
	{
		m_SlideBar->UpdateWidthRatio(m_value);
	}
	if (Input.GetKeyPressed(Keycode::A))
	{
		m_value -= 0.001;
	}
}
