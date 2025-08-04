#include "pch.h"
#include "Player.h"
#include "PlayerController.h"

void PlayerController::Awake()
{
	m_Player = GetComponent<Player>();
	m_transform = GetComponent<Transform>();	
}

void PlayerController::Start()
{
}

void PlayerController::Update(float deltaTime)
{
	if (m_Player->state == State::Alive)
	{
		int x = Input.GetAxisRaw("Horizontal");
		int y = Input.GetAxisRaw("Vertical");
		Vector2 dir{ (float)x,(float)y };
		dir.Normalize();

		if (Input.GetKeyDown(Keycode::B)) { m_Player->action = Action::Hit; }
		if (Input.GetKeyDown(Keycode::N)) { m_Player->state = State::Dead; return; }
		

		switch (m_Player->action)
		{
		case Action::Idle:
			if (dir != Vector2{ 0,0 })
			{
				m_animator->ChangeState("walk");
				m_Player->action = Action::Walk;
				break;
			}
			else if (m_animator->GetCurState() != "idle")
			{
				m_animator->ChangeState("idle");
				m_Player->action = Action::Idle;
			}
			break;
		case Action::Walk:
			if (dir == Vector2{ 0,0 })
			{
				m_Player->action = Action::Idle;
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
				m_Player->action = Action::Idle;
			}
			break;
		case Action::Steal:
			if (m_animator->GetCurState() != "steal")
			{
				m_animator->ChangeState("steal");
			}
			if (m_animator->IsAnimeEnd())
			{
				m_Player->action = Action::Idle;
			}
			break;
		}
	}

}


void PlayerController::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "crop")
	{
		if (Input.GetKeyDown(Keycode::Z)) { m_Player->action = Action::Steal; }
	}
}
