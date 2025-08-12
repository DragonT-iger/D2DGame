#include "pch.h"
#include "SpawnManager.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerSound.h"
#include "Inventory.h"
#include "ThrownCrop.h"
#include "YSort.h"
#include "OpacityDown.h"
#include "GameManager.h"

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

		//std::cout << "curDir" << curDir.x << " " << curDir.y << std::endl;

		if (m_boostTimer > 0.f)
			m_boostTimer -= deltaTime;
		else
			m_speedBoost = 0.f;

		float weight = m_inven->GetWeight();
		float weightMult = 1.f + weight / m_Player->m_weightDivisor;
		float moveSpd = std::max(
			m_Player->m_spd / (m_inven->GetSpeedMultiplier()),
			m_Player->m_minSpd);
		//std::cout << moveSpd << std::endl;

		if (m_boostTimer > 0.f)
			moveSpd += m_speedBoost;

		if (m_Player->action == Action::Walk)
			m_animator->SetSpeed(moveSpd / m_Player->m_spd);
		else
			m_animator->SetSpeed(1.f);

		if (Input.GetKeyDown(Keycode::B)) { m_Player->action = Action::Hit; }
		if (Input.GetKeyDown(Keycode::N)) { m_Player->state = State::Starve; return; }
		if (Input.GetKeyDown(Keycode::M)) { m_Player->state = State::Killed; return; }

		if (Input.GetKeyPressed(Keycode::X))
		{
			m_inven->ChangeSlot();
		}
		if (Input.GetKeyPressed(Keycode::C))
		{
			Crops type = m_inven->ThrowItem();
			if (type != Crops::Nothing)
			{
				m_throwelapsedTime = 0;
				//std::cout << "spawn" << std::endl;
				
				m_Player->m_pSound->DropCrop();
				SpawnThrownCrop(type);
				ApplyThrowBoost(type);
			}
		}
		else if (Input.GetKeyDown(Keycode::C))
		{
			m_delay += deltaTime;

			if (m_delay > m_throwDelay) {
				m_throwelapsedTime += deltaTime;
				if (m_throwelapsedTime >= m_throwTime)
				{
					Crops type = m_inven->ThrowItem();
					m_Player->m_pSound->DropCrop();
					if (type != Crops::Nothing)
					{
						m_throwelapsedTime = 0;
						SpawnThrownCrop(type);
						ApplyThrowBoost(type);
					}
				}
			}

			
		}
		else {
			m_delay = 0.f;
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
			if (m_animator->GetCurState() != "hit")
			{
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
				m_Player->action = Action::Idle;
			}
			if (m_animator->IsAnimeEnd())
			{
				m_Player->m_Inven->UpdateProfile(0);
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
		//�۹��� �浹���� �� ZŰ�� ������ Action -> Steal�� ��ȯ
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


void PlayerController::SpawnThrownCrop(Crops type)
{
	GameObject* obj = Instantiate("thrownCrop");
	auto sr = obj->AddComponent<SpriteRenderer>();
	obj->AddComponent<OpacityDown>();
	auto ys = obj->AddComponent<YSort>();
	ys->SetStatic(false);
	ys->SetOffset(50);
	
	auto thrown = obj->AddComponent<ThrownCrop>();
	auto tr = obj->GetComponent<Transform>();
	tr->SetPosition(m_transform->GetPosition());
	tr->SetScale({ 0.15f, 0.15f });

	Vector2 dir = -curDir;
	if (dir.x == 0.0f) {
		dir.x = 1.0f;
	}
	dir.y = 0;

	dir.Normalize();
	thrown->SetVelocity(dir * 300.f + Vector2{ 0.f,450.f });
	obj->GetComponent<Transform>()->Translate(Vector2{ 0, 50 });

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite;
	switch (type)
	{
	case Potato:
		sprite = ResourceManager::Instance().LoadTexture("potato_item.png");
		break;
	case Eggplant:
		sprite = ResourceManager::Instance().LoadTexture("eggplant_item.png");
		break;
	case Pumpkin:
		sprite = ResourceManager::Instance().LoadTexture("pumpkin_item.png");
		break;
	default:
		break;
	}
	sr->SetBitmap(sprite);
}

void PlayerController::ApplyThrowBoost(Crops type)
{
	switch (type)
	{
	case Potato:
		m_speedBoost = 350.f;
		break;
	case Eggplant:
		m_speedBoost = 450.f;
		break;
	case Pumpkin:
		m_speedBoost = 500.f;
		break;
	default:
		m_speedBoost = 0.f;
		break;
	}
	m_boostTimer = 0.1f;
}