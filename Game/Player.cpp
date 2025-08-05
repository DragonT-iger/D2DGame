#include "pch.h"
#include "Player.h"
#include "Inventory.h"

constexpr int	PlayerHP = 3;
constexpr float PlayerSpeed = 500.0f;
constexpr float BabyMoleStarvLevel = 500.0f;
constexpr int	invincibleTime = 15;		//60fps 기준

int Player::invincible_Count = 0;

class Inventory;

void Player::Awake()
{
	m_hp = PlayerHP;
	m_spd = PlayerSpeed;
	//starv_level = BabyMoleStarvLevel;
	m_ivc_T = invincibleTime;

	m_boxCol = GetComponent<BoxCollider>();
	m_Inven = GetComponent<Inventory>();
}

void Player::Start()
{

	m_boxCol->SetSize({ Vector2(150.f,150.f) });
}

void Player::Update(float deltaTime)
{
	//if (m_Inven->GetInvenDirty())
	//{
	//	m_spd = PlayerSpeed - (m_Inven->GetWeight());
	//} <-- 실행 안돼서 주석처리 한다
}

void Player::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Bush")
	{
		visibilty = Visibilty::Hide;
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
