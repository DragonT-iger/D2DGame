#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

void SpriteRenderer::Render(D2DRenderer* renderer, const D2D1::Matrix3x2F& viewTM)
{
	//트랜스폼 받아와서 행렬 설정 해주고
	D2D1::Matrix3x2F worldTM = m_transform->GetWorldMatrix();
	D2D1::Matrix3x2F finalTM = worldTM * viewTM;

	renderer->SetTransform(finalTM);

	// 렌더링
	renderer->DrawBitmap(*m_bitmap.GetAddressOf(), m_destRect);
}
