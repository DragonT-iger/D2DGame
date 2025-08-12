#include "pch.h"
#include "PlayerEffect.h"

void PlayerEffect::Awake()
{
	m_player = GameObject::Find("Player");
	m_animator = GetComponent<Animator>();
	m_transform = GetComponent<Transform>();

	auto hitclip = ResourceManager::Instance().LoadAnimationClip("mole_effact_final.json", "hit2");
	auto submissonclip = ResourceManager::Instance().LoadAnimationClip("mole_effact_final.json", "gain");

	m_animator->AddClip("damaged", hitclip, false);
	m_animator->AddClip("submisson", submissonclip, false);

	m_transform->SetPosition({ 0, 20 });

	GetOwner()->SetActive(false);
}

void PlayerEffect::Update(float deltaTime)
{
	if(m_animator->IsAnimeEnd())
		GetOwner()->SetActive(false);
}

void PlayerEffect::HitEffect()
{
	GetOwner()->SetActive(true);
	if (m_player->GetComponent<SpriteRenderer>()->IsFlip())
	{
		GetOwner()->GetComponent<SpriteRenderer>()->SetFlip(true);
		m_transform->SetPosition({ 50, 120 });
	}
	else
	{
		GetOwner()->GetComponent<SpriteRenderer>()->SetFlip(false);
		m_transform->SetPosition({ -50, 120 });
	}
	m_animator->ChangeState("damaged");
}

void PlayerEffect::SubMissonEffect()
{
	GetOwner()->SetActive(true);
	m_animator->ChangeState("submisson");
	m_transform->SetPosition({ 0, 20 });
}
