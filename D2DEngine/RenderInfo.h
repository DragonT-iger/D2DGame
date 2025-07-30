#pragma once
using Matrix3x2 = D2D1::Matrix3x2F;

struct RenderInfo {
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
	D2D1_RECT_F												m_destRect;
	D2D1_RECT_F												m_srcRect;
	bool													isFlip;
	int														orderLayer;
	float													opacity = 1.0f;
	Transform*											m_transform;

	bool operator<(const RenderInfo& rhs)
	{
		return orderLayer < rhs.orderLayer;
	}
};



struct UIRenderInfo {
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
	D2D1_RECT_F												m_destRect;
	D2D1_RECT_F													m_srcRect;
	int																		orderLayer;

	bool operator<(const UIRenderInfo& rhs)
	{
		return orderLayer < rhs.orderLayer;
	}
};


