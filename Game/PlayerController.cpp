#include "pch.h"
#include "SpawnManager.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerSound.h"
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
	m_inven->SetMaxCount(m_Player->maxCount);
	//p_Spd = &(m_Player->m_spd);
}

void PlayerController::Update(float deltaTime)
{
	if (m_Player->state == State::Alive)
	{
		int x = Input.GetAxisRaw("Horizontal");
		int y = Input.GetAxisRaw("Vertical");
		curDir = { (float)x,(float)y };
		curDir.Normalize();

		float weight = m_inven->GetWeight();
		float weightMult = 1.f + weight / m_Player->m_weightDivisor;
		float moveSpd = std::max(
			m_Player->m_spd / (m_inven->GetSpeedMultiplier()),
			m_Player->m_minSpd);
		//std::cout << moveSpd << std::endl;

		if (Input.GetKeyDown(Keycode::B)) { m_Player->action = Action::Hit; }
		if (Input.GetKeyDown(Keycode::N)) { m_Player->state = State::Dead; return; }

		if (Input.GetKeyPressed(Keycode::X))
		{
			m_inven->ChangeSlot();
		}
		if (Input.GetKeyPressed(Keycode::C))
		{
			if(m_inven->GetCurSlotData().count > 0)
				m_Player->m_pSound->DropCrop();
			m_inven->ThrowItem();
			m_throwelapsedTime = 0;
		}
		else if (Input.GetKeyDown(Keycode::C))
		{
			if (m_throwelapsedTime >= m_throwTime)
			{
				if (m_inven->GetCurSlotData().count > 0)
					m_Player->m_pSound->DropCrop();
				m_inven->ThrowItem();
				m_throwelapsedTime = 0;
			}
			m_throwelapsedTime += deltaTime;
		}

		/*switch (static_cast<int>(m_Player->action))
		{
		case 0:
			std::cout << "Idle" << std::endl;
			break;
		case 1:
			std::cout << "Walk" << std::endl;
			break;
		case 2:
			std::cout << "Hit" << std::endl;
			break;
		case 3:
			std::cout << "Steal" << std::endl;
			break;
		}*/

		switch (m_Player->action)
		{
		case Action::Idle:
			if (curDir != Vector2{ 0.f,0.f })
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
			if (curDir == Vector2{ 0,0 })
			{
				m_Player->action = Action::Idle;
			}
			if (!canMoveUp && curDir.y > 0) curDir.y = 0;
			if (!canMoveDown && curDir.y < 0) curDir.y = 0;
			if (!canMoveRight && curDir.x > 0) curDir.x = 0;
			if (!canMoveLeft && curDir.x < 0) curDir.x = 0;
			m_transform->Translate(curDir * moveSpd * deltaTime);
			m_Player->m_pSound->PlayWalk();
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
			if (m_animator->IsAnimeEnd())
			{
				m_Player->action = Action::Idle;
			}
			break;
		}
		//작물과 충돌중일 때 Z키를 누르면 Action -> Steal로 전환
	}
	else
	{
		if (m_animator->GetCurState() != "death2")
		{
			m_animator->ChangeState("death2");
		}
	}
}

void PlayerController::OnTriggerEnter(Collider* other)
{

}

void PlayerController::OnTriggerStay(Collider* other)
{
	auto otherObj = other->GetOwner();

	if (otherObj->GetTag() == "House" || otherObj->GetTag() == "OutRange")
	{
		auto myPos = GetComponent<Transform>()->GetPosition();
		auto otherPos = otherObj->GetComponent<Transform>()->GetPosition();
		auto collider = otherObj->GetComponent<BoxCollider>();
		auto offset = collider->GetOffset();
		auto mycol = GetComponent<BoxCollider>();

		float halfW_my = mycol->GetSize().x * 0.5f;
		float halfH_my = mycol->GetSize().y * 0.5f;

		float halfW_ot = collider->GetSize().x * 0.5f;
		float halfH_ot = collider->GetSize().y * 0.5f;

		float dx = (otherPos.x + offset.x * 0.5f) - myPos.x;
		float dy = (otherPos.y + offset.y * 0.5f) - myPos.y;

		float overlapX = (halfW_my + halfW_ot) - std::abs(dx);
		float overlapY = (halfH_my + halfH_ot) - std::abs(dy);

		if (overlapX < overlapY)
		{
			if (dx > 0)	canMoveRight = false;
			else canMoveLeft = false;
		}
		else
		{
			if (dy > 0)	canMoveUp = false;
			else			canMoveDown = false;
		}
	}

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

			if (m_inven->GetCropCount(crop_Type) == m_Player->maxCount[crop_Type])
				m_Player->m_pSound->AlreadyMaxSlot();
			else
				m_Player->m_pSound->GetCrop();
		}
	}
}

void PlayerController::OnTriggerExit(Collider* other)
{
	canMoveUp = true;
	canMoveDown = true;
	canMoveRight = true;
	canMoveLeft = true;
}
