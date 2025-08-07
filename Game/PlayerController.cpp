#include "pch.h"
#include "SpawnManager.h"
#include "Player.h"
#include "PlayerController.h"
#include "Inventory.h"

void PlayerController::Awake()
{
	m_Player = GetComponent<Player>();
	m_transform = GetComponent<Transform>();
	m_animator = GetComponent<Animator>();
}

void PlayerController::Start()
{
	m_inven = GameObject::Find("Inventory")->GetComponent<Inventory>();
	//p_Spd = &(m_Player->m_spd);
}

void PlayerController::Update(float deltaTime)
{
	if (m_Player->state == State::Alive)
	{
		int x = Input.GetAxisRaw("Horizontal");
		int y = Input.GetAxisRaw("Vertical");
		Vector2 dir{ (float)x,(float)y };
		dir.Normalize();

		float weight = m_inven->GetWeight();
		float weightMult = 1.f + weight / m_Player->m_weightDivisor;
		float moveSpd = std::max(
			m_Player->m_spd / (m_inven->GetSpeedMultiplier()),
			m_Player->m_minSpd);

		if (Input.GetKeyDown(Keycode::B)) { m_Player->action = Action::Hit; }
		if (Input.GetKeyDown(Keycode::N)) { m_Player->state = State::Dead; return; }

		if (Input.GetKeyPressed(Keycode::X))
		{
			m_inven->ChangeSlot();
		}
		if (Input.GetKeyPressed(Keycode::C))
		{
			m_inven->ThrowItem();
			m_throwelapsedTime = 0;
		}
		else if (Input.GetKeyDown(Keycode::C))
		{
			if (m_throwelapsedTime >= m_throwTime)
			{
				m_inven->ThrowItem();
				m_throwelapsedTime = 0;
			}
		}

		switch (static_cast<int>(m_Player->action))
		{
		case 0:
			//std::cout << "Idle" << std::endl;
			break;
		case 1:
			//std::cout << "Walk" << std::endl;
			break;
		case 2:
			//std::cout << "Hit" << std::endl;
			break;
		case 3:
			//std::cout << "Steal" << std::endl;
			break;
		}

		switch (m_Player->action)
		{
		case Action::Idle:
			if (dir != Vector2{ 0.f,0.f })
			{
				m_Player->action = Action::Walk;
				break;
			}
			else if (m_animator->GetCurState() != "idle")
			{
				//m_animator->ChangeState("idle");
				m_Player->action = Action::Idle;
			}
			break;
		case Action::Walk:
			if (dir == Vector2{ 0,0 })
			{
				m_Player->action = Action::Idle;
			}
			m_transform->Translate(dir * moveSpd * deltaTime);
			break;
			//case Action::Hit:
			//	if (m_animator->GetCurState() != "hit")
			//	{
			//		//m_animator->ChangeState("hit");
			//	}
			//	if (m_animator->IsAnimeEnd())
			//	{
			//		m_Player->action = Action::Idle;
			//	}
			//	break;
			// 
		case Action::Steal:
			if (m_animator->IsAnimeEnd())
			{
				m_Player->action = Action::Idle;
			}
			break;
		}
		//작물과 충돌중일 때 Z키를 누르면 Action -> Steal로 전환
	}

	m_throwelapsedTime += deltaTime;
}


void PlayerController::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "crop")
	{
		if (Input.GetKeyDown(Keycode::Z))
		{
			m_Player->action = Action::Steal;

			GameObject* crop_ptr = other->GetOwner();
			Crops crop_Type = crop_ptr->GetComponent<Crop>()->GetCropType();
			Size crop_Size = crop_ptr->GetComponent<Crop>()->GetSize();

			m_inven->AddCrop(crop_Type, crop_Size);
			m_inven->GetWeight();

			m_SpawnManager->DestroyObject(other->GetOwner());

		}
	}
}