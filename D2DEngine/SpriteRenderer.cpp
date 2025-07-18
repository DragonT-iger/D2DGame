#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::SetSize(float width, float height)
{
	if(m_transform == nullptr)
	{
		assert(false && "Ʈ�������� �ʱ�ȭ���� �ʾ���");
		return;
	}
	m_destRect = D2D1::RectF(-width / 2.0f, -height / 2.0f, width / 2.0f, height / 2.0f);

	m_transform->SetSpriteSize(D2D1::SizeF(width, height)); // Transform ���� ��������Ʈ ũ�� ����

}

// D2DRenderer �̱������� �ٲ����� ���ؼ� �Ű����� �ϳ� ��������
void SpriteRenderer::Render(const D2D1::Matrix3x2F& viewTM)
{

	D2DRenderer& renderer = D2DRenderer::Instance(); //<-- ���


	//Ʈ������ �޾ƿͼ� ��� ���� ���ְ�
	D2D1::Matrix3x2F worldTM = m_transform->GetWorldMatrix();
	D2D1::Matrix3x2F finalTM = worldTM * viewTM;

	renderer.SetTransform(finalTM);

	// ������
	renderer.DrawBitmap(*m_bitmap.GetAddressOf(), m_destRect);
}
