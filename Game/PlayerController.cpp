#include "pch.h"
#include "PlayerController.h"

void PlayerController::Awake()
{
    m_transform = GetComponent<Transform>();
    m_spriteRenderer = GetComponent<SpriteRenderer>();

}

void PlayerController::Start()
{
    WRL::ComPtr<ID2D1Bitmap1> bitmap;
    D2DRenderer::Instance()
        .CreateBitmapFromFile(L"Assets/Player.png", *bitmap.GetAddressOf());

    m_spriteRenderer->SetBitmap(bitmap);
    m_spriteRenderer->SetSize(64.f, 64.f);             // pivot Àº ±âº» Center
}

void PlayerController::Update(float deltatime)
{
    m_transform->Translate(0.02f * deltatime, 0.02f * deltatime);
    m_transform->Rotate(0.10f * deltatime);
}
