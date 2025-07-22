#pragma once
#include <wrl/client.h>
#include <d2d1_3helper.h>

using Matrix3x2 = D2D1::Matrix3x2F;

struct RenderInfo {
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;
	D2D1_RECT_F m_destRect;
	D2D1_RECT_F m_srcRect;
	D2D1::Matrix3x2F worldTM;
};
