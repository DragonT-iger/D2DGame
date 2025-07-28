#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::SetSize(float width, float height)
{
	m_renderInfo.m_destRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

	GetComponent<Transform>()->SetSpriteSize(D2D1::SizeF(width, height)); // Transform 에서 스프라이트 크기 설정
}

D2D1_SIZE_F SpriteRenderer::GetSize()
{
	float w = m_renderInfo.m_destRect.right - m_renderInfo.m_destRect.left;
	float h = m_renderInfo.m_destRect.bottom - m_renderInfo.m_destRect.top;
	return D2D1_SIZE_F{ w, h };
}

RenderInfo& SpriteRenderer::GetRenderInfo()
{
	m_renderInfo.worldTM = GetComponent<Transform>()->GetWorldMatrix();
	if (auto col = GetComponent<Collider>())
	{
		m_renderInfo.m_collider = col;
	}

	return m_renderInfo;
}
