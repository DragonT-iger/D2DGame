#include "pch.h"
#include "Button.h"

void Button::Start()
{
	m_image = GetComponent<Image>();
	m_pos = GetComponent<Transform>()->GetPosition();
	std::cout << "pos x : " << m_pos.x << ", pos y : " << m_pos.y << std::endl;
	std::cout << "width : " << m_size.width << ", height : " << m_size.height << std::endl;
}

void Button::Pressed()
{
	
}

void Button::Update(float deltaTime)
{
	auto mouse = Input.GetMouseState();


	if ((m_pos.x - (m_size.width / 2) <= mouse.pos.x && m_pos.x + (m_size.width / 2) >= mouse.pos.x)
		&& (m_pos.y - (m_size.height / 2) <= mouse.pos.y && m_pos.y + (m_size.height / 2) >= mouse.pos.y))
	{
		std::cout << "pos x : " << mouse.pos.x << ", pos y : " << mouse.pos.y << std::endl;
		m_curEvent = ButtonEvent::Highlight;
		if (mouse.LButtonPressed)
		{
			m_curEvent = ButtonEvent::Pressed;
			SetBitmap(m_curEvent);
			Pressed();
		}
		else if(m_curEvent != m_prevEvent)
		{
			SetBitmap(m_curEvent);
		}
	}
	else
	{
		m_curEvent = ButtonEvent::Idle;
		if (m_curEvent != m_prevEvent)
		{
			SetBitmap(m_curEvent);
		}
	}

	m_prevEvent = m_curEvent;
}
