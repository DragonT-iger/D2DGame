#include "pch.h"
#include "Player.h"
#include "PlayerAnimator.h"
#include "Baby.h"
#include "Inventory.h"
#include "GameManager.h"
#include "PlayerSound.h"
#include "PlayerEffect.h"

constexpr float invincibleTime = 2.0f;

class Inventory;

void Player::Awake()
{
	m_boxCol = GetComponent<BoxCollider>();
	m_baby = GetComponent<Baby>();
	m_P_animator = GetComponent<PlayerAnimator>();
	m_P_spriteRen = GetComponent<SpriteRenderer>();
	//m_animtor = GetComponent<Animator>();

	m_fullness = m_maxFullness;
	m_elapsedTime = 0.0f;

	m_hpUI.push_back(GameObject::Find("hp1"));
	m_hpUI.push_back(GameObject::Find("hp2"));
	m_hpUI.push_back(GameObject::Find("hp3"));

	m_pSound = GetComponent<PlayerSound>();
	m_pEffect = GameObject::Find("playerEffect")->GetComponent<PlayerEffect>();
}

void Player::Start()
{
	m_Inven = GameObject::Find("Inventory")->GetComponent<Inventory>();
	m_boxCol->SetSize({ Vector2(130.f,130.f) });
}

void Player::Update(float deltaTime)
{
	/*if (m_isHittable == true)
	{
		std::cout << "hitable" << std::endl;
	}
	else
	{
		std::cout << "un hit" << std::endl;
	}*/
	//m_spd = 500.0f - m_Inven->GetWeight();	//버그 버전
	m_elapsedTime += deltaTime;
	m_invincible_Count += deltaTime;

	if (0.1f <= m_elapsedTime)
	{
		if (m_fullness <= m_maxFullness && m_fullness >= (m_maxFullness / 3) * 2)
		{
			enterFullness30 = false;
			m_Inven->UpdateBabyProfile(0);
			m_Inven->UpdateHungryImg(0);
		}

		m_fullness -= m_decreaseFull;
		//m_fullness -= 10;
		m_elapsedTime = 0;
		if (m_fullness <= 0)
		{
			if (GameManager::Instance().GetGameState() == GameManager::GameState::Tutorial && !GameManager::Instance().isInvicibleMode)
				m_fullness = 1;
		}

		if (m_fullness <= (m_maxFullness / 3) * 2 && m_fullness >= (m_maxFullness / 3))
		{
			enterFullness30 = false;
			m_Inven->UpdateBabyProfile(1);
			m_Inven->UpdateHungryImg(1);
		}
		if (m_fullness <= (m_maxFullness / 3))
		{
			m_Inven->UpdateBabyProfile(2);
			m_Inven->UpdateHungryImg(2);
			if(!enterFullness30)
				m_pSound->PlayHungry30();

			enterFullness30 = true;
		}
	}

	if (invincibleTime < m_invincible_Count)
	{
		m_isHittable = true;
	}

	/*float weight = m_Inven->GetWeight();

	if (weight >= 450.f) weight = 450.f;

	m_spd = 500.0f - weight;*/

	if (m_hp <= 0 && state != State::Killed && state != State::Starve)
	{
		m_pSound->PlayDead();
		m_pSound->PlayGameOver();
		state = State::Killed;
	}
	else if (m_fullness <= 0 && state != State::Starve && state != State::Killed)
	{
		if (GameManager::GameState::Tutorial != GameManager::Instance().GetGameState() && !GameManager::Instance().isInvicibleMode) {
			m_pSound->PlayDead();
			m_pSound->PlayGameOver();
			state = State::Starve;
		}
	}

	if (state == State::Killed)
	{
		if (m_P_animator->IsDeathAnimeFinished() && !m_pSound->PlayGameOver())
		{
			std::cout << "State: Killed" << std::endl;
			GameManager::Instance().LoadEndingScene(GameManager::EndReason::PlayerDead);
		}
	}

	if (state == State::Starve)
	{
		std::cout << "State: Starve" << std::endl;
		if (m_P_animator->IsDeathAnimeFinished() && !m_pSound->PlayGameOver())
		{
			if (GameManager::GameState::Tutorial != GameManager::Instance().GetGameState() && !GameManager::Instance().isInvicibleMode) {
				GameManager::Instance().LoadEndingScene(GameManager::EndReason::BabyStarved);
			}
		}
	}

}

void Player::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Bush")
	{
		m_pSound->PlayHide();
		visibilty = Visibilty::Hide;
	}
}

void Player::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Farmer")
	{
		if (m_isHittable)
		{
			SetAction(Action::Hit);
			SetHp(GetHp() - 1);
		}
	}

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

void Player::SetHp(int hp)
{
	if (m_isHittable)
	{
		int minusHp = m_hp - hp;

		if(GameManager::Instance().GetGameState() != GameManager::GameState::Tutorial && !GameManager::Instance().isInvicibleMode){
			m_hp = hp;
		}

		m_isHittable = false;
		m_invincible_Count = 0;

		if (m_hp > -1 && state != State::Starve && GameManager::Instance().GetGameState() != GameManager::GameState::Tutorial &&!GameManager::Instance().isInvicibleMode)
		{
			for (int i = 0; i < minusHp; i++)
			{
				m_hpUI[hp + i]->SetActive(false);
			}
		}
	}

}

void Player::SubMissonEffect()
{
	m_pEffect->SubMissonEffect();
}

void Player::PlaySubmisson()
{
	m_pSound->PlaySubmission();
}

bool Player::PlayClear()
{
	return m_pSound->PlayClear();
}

void Player::FeedBaby(float bop)
{
	if (m_fullness + bop >= m_maxFullness)
		m_fullness = m_maxFullness;
	else
		m_fullness += bop;
}

void Player::OnInspectorGUI()
{
	ImGui::DragInt("HP", &m_hp, 1);
	ImGui::DragFloat("Speed", &m_spd, 0.3f, 0.1f);

	float weight = m_Inven->GetWeight();
	float weightMult = 1.f + weight / m_weightDivisor;
	float curSpd = std::max(m_spd / (m_Inven->GetSpeedMultiplier()),
		m_minSpd);

	ImGui::Text("Cur Speed : %.1f", curSpd);
}

//void Player::SetState(State ste)
//{
//	state = ste;
//}

void Player::SetAction(Action act)
{
	action = act;
}
//
//void Player::SetVisible(Visibilty vib)
//{
//	visibilty = vib;
//}