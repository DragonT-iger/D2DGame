#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::Render(D2DRenderer* renderer, const D2D1::Matrix3x2F& viewTM)
{
	//Ʈ������ �޾ƿͼ� ��� ���� ���ְ�
	D2D1::Matrix3x2F worldTM = m_transform->GetWorldMatrix();
	D2D1::Matrix3x2F finalTM = worldTM * viewTM;

	renderer->SetTransform(finalTM);

	// ������
	renderer->DrawBitmap(*m_bitmap.GetAddressOf(), m_destRect);
}
