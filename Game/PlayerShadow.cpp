#include "pch.h"
#include "PlayerShadow.h"
#include "Player.h"

void PlayerShadow::Awake()
{
	m_playerObj = SceneManager::Instance().GetActiveScene()->GetPlayer();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
}

void PlayerShadow::Start()
{
	m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("shadow.png"));
}

void PlayerShadow::Update(float deltaTime)
{
	m_spriteRenderer->SetOpacity(m_playerObj->GetComponent<SpriteRenderer>()->GetOpacity());
	
	if (m_playerObj->GetComponent<SpriteRenderer>()->IsFlip())
	{
		m_spriteRenderer->SetFlip(true);
	}
	else
	{
		m_spriteRenderer->SetFlip(false);
	}
}
