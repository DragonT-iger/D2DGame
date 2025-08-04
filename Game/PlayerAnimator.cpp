#include "pch.h"
#include "Player.h"
#include "PlayerAnimator.h"

void PlayerAnimator::Awake()
{
	m_Player = GetComponent<Player>();
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

void PlayerAnimator::Update(float deltaTime)
{
	int x = Input.GetAxisRaw("Horizontal");
	int y = Input.GetAxisRaw("Vertical");
	Vector2 dir{ (float)x,(float)y };

	if (m_Player->action == Action::Idle || m_Player->action == Action::Walk)
	{
		if (x < 0) { m_spriteRenderer->SetFlip(true); }
		else if (x > 0) { m_spriteRenderer->SetFlip(false); }
	}

	switch (m_Player->action)
	{
	case Action::Idle:
		if (dir != Vector2{ 0,0 })
		{
			m_animator->ChangeState("walk");
			break;
		}
		else if (m_animator->GetCurState() != "idle")
		{
			m_animator->ChangeState("idle");
		}
	case Action::Walk:
		if (dir == Vector2{ 0,0 })
		{
			m_animator->ChangeState("idle");
		}
	case Action::Hit:
	case Action::Steal:
		break;
	}
}
