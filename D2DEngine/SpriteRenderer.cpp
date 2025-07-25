#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::SetSize(float width, float height)
{
	m_renderInfo.m_destRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

	GetComponent<Transform>()->SetSpriteSize(D2D1::SizeF(width, height)); // Transform ���� ��������Ʈ ũ�� ����
}

RenderInfo& SpriteRenderer::GetRenderInfo()
{
	m_renderInfo.worldTM = GetComponent<Transform>()->GetWorldMatrix();

	return m_renderInfo;
}
