#include "pch.h"
#include "Player.h"

constexpr int	PlayerHP			= 3;
constexpr float PlayerSpeed			= 500.0f;
constexpr float BabyMoleStarvLevel	= 500.0f;
constexpr int	invincibleTime      = 15;		//60fps ±âÁØ

int Player::invincible_Count = 0;

void Player::Awake()
{
	hp	= PlayerHP;
	spd = PlayerSpeed;
	//starv_level = BabyMoleStarvLevel;
	ivc_T = invincibleTime;

}

void Player::OnTriggerEnter(Collider* other)
{
	//if (other->GetOwner()->GetTag() == "crop")
	//{
		//other->
	//}
}

void Player::OnTriggerStay(Collider* other)
{
	if (hp > 0)
	{
		invincible_Count++;

		if (ivc_T < invincible_Count)
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
