#include "pch.h"
#include "Player.h"
#include "PlayerAnimator.h"

void PlayerAnimator::ActionAnime()
{
	switch (m_Player->action)
	{
	case Action::Idle:
		if (m_animator->GetCurState() != "idle")
		{
			m_animator->ChangeState("idle");
		}
		break;
	case Action::Walk:
		if (m_animator->GetCurState() != "walk")
		{
			m_animator->ChangeState("walk");
		}
		break;
	case Action::Hit:
		if (m_animator->GetCurState() != "hit")
		{
			m_animator->ChangeState("hit");
		}
		break;
	case Action::Steal:
		if (m_animator->GetCurState() != "steal")
		{
			m_animator->ChangeState("steal");
		}
		break;
	}
}

void PlayerAnimator::UpdateVisible()
{
	switch (m_Player->visibilty)
	{
	case Visibilty::Visible:
		m_spriteRenderer->SetOpacity(1);
		break;
	case Visibilty::Hide:
		m_spriteRenderer->SetOpacity(0.3f);
		break;

	}

}

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
	auto moleDeath1 = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "death1");
	auto moleDeath2 = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "death2");

	m_animator->AddClip("idle", moleIdle, true);
	m_animator->AddClip("walk", molewalk, true);
	m_animator->AddClip("hit", moleHit, false);
	m_animator->AddClip("steal", moleSteal, false);
	m_animator->AddClip("death1_1", moleDeath1, false);
	m_animator->AddClip("death1_2", moleDeath1, false);
	m_animator->AddClip("death2", moleDeath2, false);

	m_animator->SetEntryState("idle");
	m_spriteRenderer->SetOpacity(1);
}

void PlayerAnimator::Update(float deltaTime)
{
	if (m_Player->state == State::Alive)
	{
		int x = Input.GetAxisRaw("Horizontal");
		int y = Input.GetAxisRaw("Vertical");
		Vector2 dir{ (float)x,(float)y };


		if (m_Player->action == Action::Idle || m_Player->action == Action::Walk)
		{
			if (x < 0) { m_spriteRenderer->SetFlip(true); }
			else if (x > 0) { m_spriteRenderer->SetFlip(false); }
		}

		ActionAnime();
		UpdateVisible();
	}
	else
	{
		if (m_animator->GetCurState() != "dead")
			m_animator->ChangeState("dead");
	}

}
