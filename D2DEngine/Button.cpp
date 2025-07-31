#include "pch.h"
#include "Button.h"

void Button::Start()
{
	m_image = GetComponent<Image>();
	m_pos = GetComponent<Transform>();
	std::cout << "pos x : " << m_pos->GetPosition().x << ", pos y : " << m_pos->GetPosition().y << std::endl;
	std::cout << "width : " << m_size.width << ", height : " << m_size.height << std::endl;
}

void Button::Pressed()
{
	for (const auto& event : m_events)
	{
		event();
	}
}

void Button::Update(float deltaTime)
{
	auto mouse = Input.GetMouseState();

	if ((m_pos->GetPosition().x - (m_size.width / 2) <= mouse.pos.x && m_pos->GetPosition().x + (m_size.width / 2) >= mouse.pos.x)
		&& (m_pos->GetPosition().y - (m_size.height / 2) <= mouse.pos.y && m_pos->GetPosition().y + (m_size.height / 2) >= mouse.pos.y))
	{
		//std::cout << "pos x : " << mouse.pos.x << ", pos y : " << mouse.pos.y << std::endl;
		if (mouse.LButtonPressed && m_curEvent != ButtonEvent::Pressed)
		{
			std::cout << "Button Pressed" << std::endl;
			m_curEvent = ButtonEvent::Pressed;
			SetBitmap(m_curEvent);
			Pressed();
		}
		else if(!mouse.LButtonPressed && m_curEvent != ButtonEvent::Highlight)
		{
			m_curEvent = ButtonEvent::Highlight;
			SetBitmap(m_curEvent);
		}
	}
	else
	{
		if (m_curEvent != ButtonEvent::Idle)
		{
			m_curEvent = ButtonEvent::Idle;
			SetBitmap(m_curEvent);
		}
	}
}
