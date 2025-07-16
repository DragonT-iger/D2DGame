#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

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
