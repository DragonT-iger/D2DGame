#pragma once
#include <array>

enum class ButtonEvent : size_t
{
	Idle = 0,
	Highlight = 1,
	Pressed = 2,
	ButtonDown = 3,
	Selected = 4,
	Disabled = 5,

	MaxEvent
};

class Button : public MonoBehaviour
{
public:
	Button() = default;
	virtual ~Button() = default;

	void Start() override;

	void AddEventSprite(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite, ButtonEvent event) {
		m_sprites[static_cast<int>(event)] = sprite;
	}

	void AddEvent(std::function<void()> event, ButtonEvent btnevent)
	{
		switch (btnevent)
		{
		case ButtonEvent::Highlight:
			m_highlightEvents.push_back(event);
			break;
		case ButtonEvent::Pressed:
			m_pressedEvents.push_back(event);
			break;
		case ButtonEvent::ButtonDown:
			m_downEvents.push_back(event);
			break;
		default:
			break;
		}
	}

	void SetBitmap(ButtonEvent event) { 
		if(m_sprites[static_cast<size_t>(event)])	
			m_image->SetBitmap(m_sprites[static_cast<size_t>(event)], m_size); 
	}
	void SetSize(Vector2 size) { m_size = { size.x, size.y }; }

	void Event(ButtonEvent event);

	void Update(float deltaTime);

private:
	Image*																				m_image;
	D2D1_SIZE_F													m_size = { 160.f, 40.f };
	Transform*																					m_pos;
	ButtonEvent								m_curEvent = ButtonEvent::MaxEvent;
	std::vector<std::function<void()>>									m_highlightEvents;
	std::vector<std::function<void()>>									m_pressedEvents;
	std::vector<std::function<void()>>									m_downEvents;
	std::array<Microsoft::WRL::ComPtr<ID2D1Bitmap1>, static_cast<size_t>(ButtonEvent::MaxEvent)> m_sprites;
};


