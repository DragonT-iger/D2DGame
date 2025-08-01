#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::SetSize(float width, float height)
{
	m_renderInfo.m_destRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

	GetComponent<Transform>()->SetSpriteSize(D2D1::SizeF(width, height)); // Transform 에서 스프라이트 크기 설정
}

void SpriteRenderer::OnInspectorGUI()
{

    // ── 텍스처 핸들 ─────────────────────────────────────────────
    ImGui::Text("Bitmap : %p", m_renderInfo.m_bitmap.Get());

    // ── SrcRect ------------------------------------------------
    float src[4] = { m_renderInfo.m_srcRect.left,  m_renderInfo.m_srcRect.top,
                     m_renderInfo.m_srcRect.right, m_renderInfo.m_srcRect.bottom };
    if (ImGui::DragFloat4("SrcRect", src))
    {
        m_renderInfo.m_srcRect = { src[0], src[1], src[2], src[3] };
        SetSrcRect(m_renderInfo.m_srcRect);      
    }

    D2D1_SIZE_F sz = GetSize();
    float size[2] = { sz.width, sz.height };
    if (ImGui::DragFloat2("Size", size))
    {
        SetSize(size[0], size[1]); 
    }

    if (ImGui::SliderFloat("Opacity", &m_renderInfo.opacity, 0.0f, 1.0f))
    {
        SetOpacity(m_renderInfo.opacity);
    }

    int order = m_renderInfo.orderLayer;
    if (ImGui::DragInt("Order", &order))
    {
        SetOrderInLayer(order);
    }

    bool flip = m_renderInfo.isFlip;
    if (ImGui::Checkbox("Flip", &flip))
    {
        SetFlip(flip);
    }
}

D2D1_SIZE_F SpriteRenderer::GetSize()
{
	float w = m_renderInfo.m_destRect.right - m_renderInfo.m_destRect.left;
	float h = m_renderInfo.m_destRect.bottom - m_renderInfo.m_destRect.top;
	return D2D1_SIZE_F{ w, h };
}

RenderInfo& SpriteRenderer::GetRenderInfo()
{
	m_renderInfo.m_transform = GetComponent<Transform>();

	return m_renderInfo;
}
