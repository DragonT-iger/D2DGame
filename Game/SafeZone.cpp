#include "pch.h"
#include "SafeZone.h"



void SafeZone::Awake()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	tr->SetPosition({ m_x, m_y });

	tr->SetScale({ 1.0f, 1.0f });
	m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();


	ComPtr<ID2D1Bitmap1> tree_sprite;

	tree_sprite = ResourceManager::Instance().LoadTexture("safe_zone_bush.png");
	m_spriteRenderer->SetBitmap(tree_sprite);
}

//void SafeZone::OnTriggerEnter(Collider* other)
//{
//	if (other->GetOwner()->GetName() == "Player")
//	{
//		m_spriteRenderer->SetOpacity(0.3f);
//	}
//}

//void SafeZone::OnTriggerExit(Collider* other)
//{
//	if (other->GetOwner()->GetName() == "Player")
//	{
//		m_spriteRenderer->SetOpacity(1.0f);
//	}
//}
