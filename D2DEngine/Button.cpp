#include "pch.h"
#include "Button.h"

void Button::Start()
{
	m_image = GetComponent<Image>();
	m_pos = GetComponent<Transform>();
	std::cout << "pos x : " << m_pos->GetPosition().x << ", pos y : " << m_pos->GetPosition().y << std::endl;
	std::cout << "width : " << m_size.width << ", height : " << m_size.height << std::endl;
}

void Button::Event(ButtonEvent event)
{
	switch (event)
	{
	case ButtonEvent::Idle:
		for (const auto& event : m_idleEvents)
		{
			event();
		}
		break;
	case ButtonEvent::Highlight:
		for (const auto& event : m_highlightEvents)
		{
			event();
		}
		break;
	case ButtonEvent::Pressed:
		for (const auto& event : m_pressedEvents)
		{
			event();
		}
		break;
	case ButtonEvent::ButtonDown:
		for (const auto& event : m_downEvents)
		{
			event();
		}
		break;
	}
}

void Button::Update(float deltaTime)
{
	auto mouse = Input.GetMouseState();

	if ((m_pos->GetPosition().x - (m_size.width / 2) <= mouse.pos.x && m_pos->GetPosition().x + (m_size.width / 2) >= mouse.pos.x)
		&& (m_pos->GetPosition().y - (m_size.height / 2) <= mouse.pos.y && m_pos->GetPosition().y + (m_size.height / 2) >= mouse.pos.y))
	{
		//std::cout << "pos x : " << mouse.pos.x << ", pos y : " << mouse.pos.y << std::endl;
		if (mouse.LButtonPressed && m_curEvent != ButtonEvent::Pressed && m_curEvent != ButtonEvent::ButtonDown)
		{
			std::cout << "Button Pressed" << std::endl;
			m_curEvent = ButtonEvent::Pressed;
			SetBitmap(m_curEvent);
			Event(ButtonEvent::Pressed);
		}
		else if (mouse.LButtonPressed)
		{
			m_curEvent = ButtonEvent::ButtonDown;
			Event(ButtonEvent::ButtonDown);
		}
		else if(!mouse.LButtonPressed && m_curEvent != ButtonEvent::Highlight)
		{
			m_curEvent = ButtonEvent::Highlight;
			SetBitmap(m_curEvent);
			Event(ButtonEvent::Highlight);
		}
	}
	else
	{
		if (m_curEvent != ButtonEvent::Idle)
		{
			m_curEvent = ButtonEvent::Idle;
			SetBitmap(m_curEvent);
			Event(ButtonEvent::Idle);
		}
	}
}
