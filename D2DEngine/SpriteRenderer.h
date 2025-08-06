#pragma once  
#include "MonoBehaviour.h"
#include "RenderInfo.h"
#include "Transform.h"


class SpriteRenderer : public MonoBehaviour
{
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() = default;

#ifdef _DEBUG
	void OnInspectorGUI() override;
#endif

	void SetBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap1>& bitmap) {
		m_renderInfo.m_bitmap = bitmap;
		if (bitmap == nullptr) {
			m_renderInfo.m_srcRect = { 0.f, 0.f, 0.f, 0.f };
		}
		else {
			m_renderInfo.m_srcRect = { 0.f, 0.f, bitmap->GetSize().width, bitmap->GetSize().height };
		}
		float w = m_renderInfo.m_srcRect.right - m_renderInfo.m_srcRect.left;
		float h = m_renderInfo.m_srcRect.bottom - m_renderInfo.m_srcRect.top;
		m_renderInfo.m_destRect = { -(w / 2), -(h / 2), w / 2 , h / 2 };
	}

	void SetOpacity(float opacity) {
		if (opacity > 1.0f)
			opacity = 1.0f;
		else if (opacity < 0.f)
			opacity = 0.0f;

		m_renderInfo.opacity = opacity;
	}

	D2D1_SIZE_F GetSize();
	void SetSize(float width, float height);

	void SetSrcRect(const D2D1_RECT_F& rect) {
		m_renderInfo.m_srcRect = rect;
		m_renderInfo.m_destRect = { -(rect.right - rect.left) / 2, -(rect.bottom - rect.top) / 2, (rect.right - rect.left) / 2 , (rect.bottom - rect.top) / 2 };
	}

	void SetOrderInLayer(int ord) { m_renderInfo.orderLayer = ord; }

	void SetFlip(bool flip) { m_renderInfo.isFlip = flip; }
	bool IsFlip() { return m_renderInfo.isFlip; }

	RenderInfo& GetRenderInfo();

private:
	RenderInfo                                                  m_renderInfo; //렌더링 정보, 애니메이션이면 애니메이션 정보가 들어감
};
