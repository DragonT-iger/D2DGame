#include "pch.h"
#include "Player.h"
#include "Inventory.h"

int Player::invincible_Count = 0;

class Inventory;

void Player::Awake()
{
	m_boxCol = GetComponent<BoxCollider>();
}

void Player::Start()
{
	m_Inven = GameObject::Find("Inventory")->GetComponent<Inventory>();
	m_boxCol->SetSize({ Vector2(150.f,150.f) });
}

void Player::Update(float deltaTime)
{
	m_spd = 500.0f - m_Inven->GetWeight();
}

void Player::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Bush")
	{
		visibilty = Visibilty::Hide;
	}

	if (other->GetOwner()->GetTag() == "SubMissionArea")
	{
		std::vector<SlotData> temp = m_Inven->SubMissonItem();
		
	}
}

void Player::OnTriggerStay(Collider* other)
{
	/*if (m_hp > 0)
	{
		invincible_Count++;

		if (m_ivc_T < invincible_Count)
		{
			action = Action::Hit;
			invincible_Count = 0;
		}
	}
	else
	{
		state = State::Dead;
	}*/

}

void Player::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Bush")
	{
		visibilty = Visibilty::Visible;
	}

}

//void Player::SetState(State ste)
//{
//	state = ste;
//}
//
//void Player::SetAction(Action act)
//{
//	action = act;
//}
//
//void Player::SetVisible(Visibilty vib)
//{
//	visibilty = vib;
//}
