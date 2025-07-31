#pragma once
#include <array>

enum class ButtonEvent : size_t
{
	Idle = 0,
	Highlight = 1,
	Pressed = 2,
	Selected = 3,
	Disabled = 4,

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

	void AddPressEvent(std::function<void()> event)
	{
		m_events.push_back(event);
	}

	void SetBitmap(ButtonEvent event) { 
		if(m_sprites[static_cast<size_t>(event)])	
			m_image->SetBitmap(m_sprites[static_cast<size_t>(event)], m_size); 
	}
	void SetSize(Vector2 size) { m_size = { size.x, size.y }; }

	void Pressed();

	void Update(float deltaTime);

private:
	Image*																				m_image;
	D2D1_SIZE_F													m_size = { 160.f, 40.f };
	Transform*																					m_pos;
	ButtonEvent								m_curEvent = ButtonEvent::MaxEvent;
	std::vector<std::function<void()>>									m_events;
	std::array<Microsoft::WRL::ComPtr<ID2D1Bitmap1>, static_cast<size_t>(ButtonEvent::MaxEvent)> m_sprites;
};


