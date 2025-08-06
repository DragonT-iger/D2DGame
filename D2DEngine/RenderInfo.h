#pragma once
using Matrix3x2 = D2D1::Matrix3x2F;

struct RenderInfo {
	bool													isFlip;
	int														orderLayer;
	float													opacity = 1.0f;
	Transform*										m_transform;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
	D2D1_RECT_F												m_destRect;
	D2D1_RECT_F												m_srcRect;
	
	bool operator<(const RenderInfo& rhs)
	{
		return orderLayer < rhs.orderLayer;
	}
};



struct UIRenderInfo {
	std::wstring_view													m_text;
	std::wstring_view													m_font;
	int																			fontSize = 15;
	int																		orderLayer;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap = nullptr;
	D2D1_RECT_F													m_destRect;
	D2D1_RECT_F													m_srcRect;
	D2D1_RECT_F													m_layoutRect;
	D2D1::ColorF									m_color = D2D1::ColorF::White;
	
	bool operator<(const UIRenderInfo& rhs)
	{
		return orderLayer < rhs.orderLayer;
	}
};


