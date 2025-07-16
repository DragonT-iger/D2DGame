#include "pch.h"
#include "SpriteRenderer.h"
#include "D2DRenderer.h"

// D2DRenderer 싱글톤으로 바꿈으로 인해서 매개변수 하나 제거했음
void SpriteRenderer::Render(const D2D1::Matrix3x2F& viewTM)
{

	D2DRenderer& renderer = D2DRenderer::Instance(); //<-- 요거


	//트랜스폼 받아와서 행렬 설정 해주고
	D2D1::Matrix3x2F worldTM = m_transform->GetWorldMatrix();
	D2D1::Matrix3x2F finalTM = worldTM * viewTM;

	renderer.SetTransform(finalTM);

	// 렌더링
	renderer.DrawBitmap(*m_bitmap.GetAddressOf(), m_destRect);
}
