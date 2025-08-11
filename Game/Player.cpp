#include "pch.h"
#include "Player.h"
#include "PlayerAnimator.h"
#include "Baby.h"
#include "Inventory.h"
#include "GameManager.h"

int Player::invincible_Count = 0;

class Inventory;

void Player::Awake()
{
	m_boxCol = GetComponent<BoxCollider>();
	m_baby = GetComponent<Baby>();
	m_P_animator = GetComponent<PlayerAnimator>();

	m_fullness = 1000.0f;
	m_elapsedTime = 0.0f;

	m_hpUI.push_back(GameObject::Find("hp1"));
	m_hpUI.push_back(GameObject::Find("hp2"));
	m_hpUI.push_back(GameObject::Find("hp3"));
}

void Player::Start()
{
	m_Inven = GameObject::Find("Inventory")->GetComponent<Inventory>();
	m_boxCol->SetSize({ Vector2(130.f,130.f) });
}

void Player::Update(float deltaTime)
{
	//m_spd = 500.0f - m_Inven->GetWeight();	//버그 버전
	m_elapsedTime += deltaTime;

	if (0.1f <= m_elapsedTime)
	{
		m_fullness -= 1.0f;
		m_elapsedTime = 0.0f;
	}

	/*float weight = m_Inven->GetWeight();

	if (weight >= 450.f) weight = 450.f;

	m_spd = 500.0f - weight;*/

	if (m_hp <= 0 && state != State::Killed)
	{
		state = State::Killed;
	}
	else if(m_fullness <= 0 &&state != State::Starve)
	{
		state = State::Starve;
	}

	if (state == State::Killed)
	{
		if (m_P_animator->IsDeathAnimeFinished())
		{


			std::cout << "State: Killed" << std::endl;
			GameManager::Instance().LoadEndingScene(GameManager::EndReason::PlayerDead);
		}

	}

	if (state == State::Starve)
	{
		std::cout << "State: Starve" << std::endl;
		if (m_P_animator->IsDeathAnimeFinished())
		{
			GameManager::Instance().LoadEndingScene(GameManager::EndReason::BabyStarved);
		}
	}
		
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

void Player::FeedBaby(float bop)
{
	if (m_fullness + bop >= 1000.f)
		m_fullness = 1000.f;
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
