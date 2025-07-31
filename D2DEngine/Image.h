#pragma once

class Image : public MonoBehaviour
{
public:
	Image() = default;
	virtual ~Image() = default;

	void Awake() {
		m_pos = GetComponent<Transform>();
	}

	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap, D2D1_SIZE_F size) { 
		m_pos = GetComponent<Transform>();
		m_size = size;
		m_renderInfo.m_bitmap = bitmap;
		m_renderInfo.m_destRect = { -(m_size.width / 2) + m_pos->GetPosition().x , -(m_size.height / 2) + m_pos->GetPosition().y, (m_size.width / 2) + m_pos->GetPosition().x , (m_size.height / 2) + m_pos->GetPosition().y };
		m_renderInfo.m_srcRect = { 0, 0, bitmap->GetSize().width, bitmap->GetSize().height };
	}

	void SetSrcRect(D2D1_RECT_F rect)
	{
		m_renderInfo.m_srcRect = rect;
	}
	void Update(float deltaTime) override {
		m_renderInfo.m_destRect = { -(m_size.width / 2) + m_pos->GetPosition().x , -(m_size.height / 2) + m_pos->GetPosition().y, (m_size.width / 2) + m_pos->GetPosition().x , (m_size.height / 2) + m_pos->GetPosition().y };
	}

	void SetDestRect(D2D1_RECT_F rect)
	{
		m_renderInfo.m_destRect = rect;
	}

	void SetOrderInLayer(int ord) { m_renderInfo.orderLayer = ord; }

	UIRenderInfo& GetRenderInfo() { return m_renderInfo; }

private:
	Transform*								m_pos;
	D2D1_SIZE_F							m_size;
	UIRenderInfo				m_renderInfo;
};
