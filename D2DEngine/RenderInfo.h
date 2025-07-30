#pragma once
#include <wrl/client.h>
#include <d2d1_3helper.h>
#include "Collider.h"

using Matrix3x2 = D2D1::Matrix3x2F;

struct RenderInfo {
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
	D2D1_RECT_F												m_destRect;
	D2D1_RECT_F													m_srcRect;
	bool																			isFlip;
	int																		orderLayer;
	float																opacity = 1.0f;
	D2D1::Matrix3x2F												worldTM;
	Collider*															m_collider;	//디버그용

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


