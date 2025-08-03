#include "pch.h"
#include "player.h"
#include "PlayerController.h"

void PlayerController::Awake()
{
	m_Player = GetComponent<Player>();
	m_transform = GetComponent<Transform>();
	
}

void PlayerController::Start()
{
	c_state = m_Player->GetState_adr();
	c_action = m_Player->GetAction_adr();
	c_visibilty = m_Player->GetVisibilty_adr();

	p_Spd = m_Player->GetSpd_adr();
}

void PlayerController::Update(float deltaTime)
{
	if (*c_state == State::Alive)
	{
		int x = Input.GetAxisRaw("Horizontal");
		int y = Input.GetAxisRaw("Vertical");
		Vector2 dir{ (float)x,(float)y };
		dir.Normalize();

		if (*c_action == Action::Idle || *c_action == Action::Walk)
		{
			if (x < 0) { m_spriteRenderer->SetFlip(true); }
			else if (x > 0) { m_spriteRenderer->SetFlip(false); }
		}
		
		if (Input.GetKeyDown(Keycode::B)) { *c_action = Action::Hit; }
		if (Input.GetKeyDown(Keycode::N)) { m_animator->ChangeState("dead"); state = State::Dead; return; }
		

		switch (*c_action)
		{
		case Action::Idle:
			if (dir != Vector2{ 0,0 })
			{
				m_animator->ChangeState("walk");
				*c_action = Action::Walk;
				break;
			}
			else if (m_animator->GetCurState() != "idle")
			{
				m_animator->ChangeState("idle");
				*c_action = Action::Idle;
			}
			break;
		case Action::Walk:
			if (dir == Vector2{ 0,0 })
			{
				m_animator->ChangeState("idle");
				*c_action = Action::Idle;
			}
			m_transform->Translate(dir * (*p_Spd) * deltaTime);
			break;
		case Action::Hit:
			if (m_animator->GetCurState() != "hit")
			{
				m_animator->ChangeState("hit");
			}
			if (m_animator->IsAnimeEnd())
			{
				*c_action = Action::Idle;
			}
			break;
		case Action::Steal:
			if (m_animator->GetCurState() != "steal")
			{
				m_animator->ChangeState("steal");
			}
			if (m_animator->IsAnimeEnd())
			{
				*c_action = Action::Idle;
			}
			break;
		}
	}

}


void PlayerController::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "crop")
	{
		if (Input.GetKeyDown(Keycode::Z)) { action = Action::Steal; }
	}
}
