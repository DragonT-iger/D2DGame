#include "pch.h"
#include "Slide_Bar.h"

void Slide_Bar::Start()
{
	m_Image = GetComponent<Image>();
	m_orignal = m_Image->GetSize();
}

void Slide_Bar::UpdateWidthRatio(float v)
{
	if (v > 1.0f) v = 1.0f;
	else if (v < 0.0f) v = 0.0f;
	value = v;
	D2D1_RECT_F destRect = m_Image->GetRenderInfo().m_destRect;
	float ratio = m_orignal.width * value;
	destRect.right = destRect.left + ratio;
	m_Image->SetDestRect(destRect);
}

void Slide_Bar::UpdateHeightRatio(float v)
{
	v = v > 1.0f ? 1.0f : v;
	value = v;
	D2D1_RECT_F destRect = m_Image->GetRenderInfo().m_destRect;
	float ratio = m_orignal.height * value;
	destRect.top = destRect.bottom - ratio;
	m_Image->SetDestRect(destRect);
}

void Slide_Bar::RegisterButton(Button* handleButton)
{
	m_button = handleButton;
	
	/*if (!m_Image)
	{
		m_Image = GetComponent<Image>();
		m_orignal = m_Image->GetSize();
	}*/

	m_button->AddPressEvent([this]() {
		auto mPos = Input.GetMouseState().pos;
		Vector2 mousePos = { static_cast<float>(mPos.x),  static_cast<float>(mPos.y) };
		D2D1_RECT_F barRect = m_Image->GetRenderInfo().m_destRect;

		// 이동 가능한 최소/최대 X
		float minX = barRect.left;
		float maxX = barRect.left + m_orignal.width;

		if (mPos.x < minX) mousePos.x = minX;
		if (mPos.x > maxX) mousePos.x = maxX;

		value = (mousePos.x - minX) / (maxX - minX);
		UpdateWidthRatio(value);
		});
}
