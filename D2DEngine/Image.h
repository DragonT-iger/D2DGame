#pragma once

class Image : public MonoBehaviour
{
public:
	Image() = default;
	virtual ~Image() = default;

	void Start() override;

	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap, D2D1_SIZE_F size) { 
		m_renderInfo.m_bitmap = bitmap;
		m_renderInfo.m_destRect = { -(size.width / 2) + m_pos.x, -(size.height / 2) + m_pos.y, (size.width / 2) + m_pos.x , (size.height / 2) + m_pos.y };
	}

	void SetOrderInLayer(int ord) { m_renderInfo.orderLayer = ord; }

	UIRenderInfo& GetRenderInfo() { return m_renderInfo; }

private:
	Vector2									m_pos;
	UIRenderInfo				m_renderInfo;
};
