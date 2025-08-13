#include "pch.h"
#include "SafeBush.h"

void SafeBush::Awake()
{
	m_spriteRenderer = GetComponent<SpriteRenderer>();

	m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("safe_zone_bush.png"));
}

void SafeBush::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetName() == "Player")
	{
		m_spriteRenderer->SetOpacity(0.5f);
	}
}

void SafeBush::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetName() == "Player")
	{
		m_spriteRenderer->SetOpacity(1);
	}
}
