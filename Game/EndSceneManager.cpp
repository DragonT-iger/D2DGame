#include "pch.h"
#include "EndSceneManager.h"
#include "GameManager.h"

void EndSceneManager::Awake()
{
	m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();

	


}

void EndSceneManager::Start()
{
	switch (GameManager::Instance().GetEndReason())
	{
	case GameManager::EndReason::None:
		m_spriteRenderer->SetBitmap(nullptr);

		break;

	case GameManager::EndReason::BabyStarved:
		m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BadEnding2.png"));

		break;

	case GameManager::EndReason::PlayerDead:
		m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BadEnding1.png"));

		break;

	case GameManager::EndReason::Happy:
		m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("HappyEnd.png"));
		break;

	default:
		break;
	}
}
