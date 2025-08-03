#include "pch.h"
#include "Player.h"
#include "PlayerAnimator.h"

void PlayerAnimator::Awake()
{
	m_spriteRenderer = GetComponent<SpriteRenderer>();
	m_animator = GetComponent<Animator>();
}

void PlayerAnimator::Start()
{
	auto moleIdle = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "idle");
	auto molewalk = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "walk");
	auto moleHit = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "hit");
	auto moleSteal = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "steal");
	auto moleDead = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "dead");

	m_animator->AddClip("idle", moleIdle, true);
	m_animator->AddClip("walk", molewalk, true);
	m_animator->AddClip("hit", moleHit, false);
	m_animator->AddClip("steal", moleSteal, false);
	m_animator->AddClip("dead", moleDead, false);

	m_animator->SetEntryState("idle");
	m_spriteRenderer->SetOpacity(1);
}
