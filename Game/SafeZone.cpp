#include "pch.h"
#include "SafeZone.h"



void SafeZone::Awake()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	tr->SetPosition({ m_x, m_y });
	tr->Translate({ 0 , 200 });

	tr->SetScale({ 0.5f, 0.5f });
	m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();


	ComPtr<ID2D1Bitmap1> tree_sprite;

	tree_sprite = ResourceManager::Instance().LoadTexture("safe_zone.png");
	m_spriteRenderer->SetBitmap(tree_sprite);

}
