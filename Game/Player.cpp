#include "pch.h"
#include "Player.h"
#include "Inventory.h"
#include "GameManager.h"

int Player::invincible_Count = 0;

class Inventory;

void Player::Awake()
{
	m_boxCol = GetComponent<BoxCollider>();

	m_fullness = 1000.0f;
	m_elapsedTime = 0.0f;
}

void Player::Start()
{
	m_Inven = GameObject::Find("Inventory")->GetComponent<Inventory>();
	m_boxCol->SetSize({ Vector2(150.f,150.f) });
}

void Player::Update(float deltaTime)
{
	//m_spd = 500.0f - m_Inven->GetWeight();	//버그 버전
	m_elapsedTime += deltaTime;

	if (2.0f <= m_elapsedTime)
	{
		m_fullness -= 20.0f;
		m_elapsedTime = 0.0f;
	}

	float weight = m_Inven->GetWeight();

	if (weight >= 450.f) weight = 450.f;

	m_spd = 500.0f - weight;
}

void Player::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Bush")
	{
		visibilty = Visibilty::Hide;
	}

	if (other->GetOwner()->GetTag() == "SubMissionArea")
	{
		int bob = GameManager::Instance().ReceiveScore(m_Inven->SubMissonItem());
		FeedBaby(bob);
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

void Player::FeedBaby(float bop)
{
	if (m_fullness + bop >= 1000.f)
		m_fullness = 1000.f;
	else
		m_fullness += bop;
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
