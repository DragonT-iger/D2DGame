#include "pch.h"
#include "Player.h"

constexpr int	PlayerHP			= 3;
constexpr float PlayerSpeed			= 500.0f;
constexpr float BabyMoleStarvLevel	= 500.0f;
constexpr int	invincibleTime      = 15;		//60fps ±âÁØ

int Player::invincible_Count = 0;

void Player::Awake()
{
	m_hp = PlayerHP;
	m_spd = PlayerSpeed;
	//starv_level = BabyMoleStarvLevel;
	m_ivc_T = invincibleTime;

}

void Player::OnTriggerEnter(Collider* other)
{
}

void Player::OnTriggerStay(Collider* other)
{
	if (m_hp > 0)
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
	}
	
}

void Player::OnTriggerExit(Collider* other)
{

}
