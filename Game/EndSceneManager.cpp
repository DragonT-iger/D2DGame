#include "pch.h"
#include "EndSceneManager.h"
#include "GameManager.h"

void EndSceneManager::Awake()
{
	m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();

	m_animator = GetOwner()->AddComponent<Animator>();

	//auto title = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "title");
	auto killed = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "killed");
	auto starve = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "starve");
	auto happy = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "happy");

	//m_animator->AddClip("title", title, true);
	m_animator->AddClip("killed", killed, true);
	m_animator->AddClip("starve", starve, true);
	m_animator->AddClip("happy", happy, true);
}

void EndSceneManager::Start()
{
	switch (GameManager::Instance().GetEndReason())
	{
	case GameManager::EndReason::None:
		m_spriteRenderer->SetBitmap(nullptr);

		break;

	case GameManager::EndReason::BabyStarved:
		//m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BadEnding2.png"));
		m_animator->ChangeState("starve");
		break;

	case GameManager::EndReason::PlayerDead:
		//m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BadEnding1.png"));
		m_animator->ChangeState("killed");
		break;

	case GameManager::EndReason::Happy:
		//m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("HappyEnd.png"));
		m_animator->ChangeState("happy");
		break;

	default:
		break;
	}
}
