#include "pch.h"
#include "EndSceneManager.h"
#include "GameManager.h"

void EndSceneManager::Awake()
{
	m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();

	m_animator = GetOwner()->AddComponent<Animator>();

	m_endingNumImage = GameObject::Find("EndingNum")->GetComponent<Image>();
}

void EndSceneManager::Start()
{
	//auto title = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "title");
	auto killed = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "killed");
	auto starve = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "starve");
	auto happy = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "happy");

	//m_animator->AddClip("title", title, true);
	m_animator->AddClip("killed", killed, true);
	m_animator->AddClip("starve", starve, true);
	m_animator->AddClip("happy", happy, true);

	switch (GameManager::Instance().GetEndReason())
	{
	case GameManager::EndReason::None:
		m_spriteRenderer->SetBitmap(nullptr);

		break;

	case GameManager::EndReason::BabyStarved:
		//m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BadEnding2.png"));
		m_animator->ChangeState("starve");
		m_endingNumImage->SetBitmap(ResourceManager::Instance().LoadTexture("Ending3_Bad.png"), { 505, 150 });
		SoundManager::Instance().BGM_Shot("6.mp3");
		break;

	case GameManager::EndReason::PlayerDead:
		//m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BadEnding1.png"));
		m_animator->ChangeState("killed");
		m_endingNumImage->SetBitmap(ResourceManager::Instance().LoadTexture("Ending2_Bad.png"), { 505, 150 });
		SoundManager::Instance().BGM_Shot("5.mp3");
		break;

	case GameManager::EndReason::Happy:
		//m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("HappyEnd.png"));
		m_animator->ChangeState("happy");
		m_endingNumImage->SetBitmap(ResourceManager::Instance().LoadTexture("Ending1_Happy.png"), { 600, 160 });
		SoundManager::Instance().BGM_Shot("4.mp3");
		break;

	default:
		break;
	}
}
