#pragma once  
#include "MonoBehaviour.h"
#include "RenderInfo.h"
#include "Transform.h"


class SpriteRenderer : public MonoBehaviour
{
public:
	SpriteRenderer() = default;
	virtual ~SpriteRenderer() {
		ULONG refCount = m_renderInfo.m_bitmap->AddRef();
		refCount = m_renderInfo.m_bitmap->Release();
		std::cout << "refCount : " << refCount << std::endl;
	}

	void Awake() override;

	void SetBitmap(const Microsoft::WRL::ComPtr<ID2D1Bitmap1>& bitmap) {
		m_renderInfo.m_bitmap = bitmap;
	}  //�⺻ ��������Ʈ ����

	void SetSize(float width, float height);

	void SetSrcRect(const D2D1_RECT_F& rect) {
		m_renderInfo.m_srcRect = rect;
		m_renderInfo.m_destRect = { 0, 0, rect.right - rect.left, rect.bottom - rect.top };
	}

	RenderInfo& GetRenderInfo();

private:
	Transform*									m_transform = nullptr;
	RenderInfo                                                  m_renderInfo; //������ ����, �ִϸ��̼��̸� �ִϸ��̼� ������ ��
};
