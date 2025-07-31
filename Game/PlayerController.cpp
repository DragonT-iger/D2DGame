#include "pch.h"
#include "PlayerController.h"



void PlayerController::Awake()
{
	m_transform = GetComponent<Transform>();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
	m_animator = GetComponent<Animator>();
	auto collider = GetComponent<CircleCollider>();

	str_currentState = "idle";
}

void PlayerController::Start()
{
	auto moleIdle = ResourceManager::Instance().LoadAnimationClip("mole.json", "idle");
	auto molewalk = ResourceManager::Instance().LoadAnimationClip("mole.json", "walk");
	auto moleHit = ResourceManager::Instance().LoadAnimationClip("mole.json", "hit");
	auto moleSteal = ResourceManager::Instance().LoadAnimationClip("mole.json", "steal");
	auto moleDead = ResourceManager::Instance().LoadAnimationClip("mole.json", "dead");

	m_animator->AddClip("idle", moleIdle,true);
	m_animator->AddClip("walk", molewalk,true);
	m_animator->AddClip("hit", moleHit,false);
	m_animator->AddClip("steal", moleSteal,false);
	m_animator->AddClip("dead", moleDead,false);

	m_animator->SetEntryState("idle");

	auto collider = GetComponent<BoxCollider>();

	collider->SetSize({ 100, 100 });
	m_spriteRenderer->SetOpacity(1);
}

void PlayerController::Update(float deltaTime)
{
	if (Input.GetKeyDown(Keycode::UP))			{ state = Action::Walk; m_transform->Translate(0, m_Spd_Y * deltaTime); }
	else if (Input.GetKeyDown(Keycode::DOWN))	{ state = Action::Walk; m_transform->Translate(0, -m_Spd_Y * deltaTime); }
	else if (Input.GetKeyDown(Keycode::LEFT))  { state = Action::Walk; m_transform->Translate(-m_Spd_X * deltaTime, 0); if (!m_spriteRenderer->IsFlip()) m_spriteRenderer->SetFlip(true); }
	else if (Input.GetKeyDown(Keycode::RIGHT))  { state = Action::Walk; m_transform->Translate(m_Spd_X * deltaTime, 0); if(m_spriteRenderer->IsFlip()) m_spriteRenderer->SetFlip(false); }
	else if (Input.GetKeyDown(Keycode::Z))		{ state = Action::Steal; }
	else if (Input.GetKeyDown(Keycode::Q))		{ state = Action::Dead; }
	else if (Input.GetKeyDown(Keycode::W))		 { state = Action::Hit; }


	switch (state)
	{
	case Action::Idle:
		if (str_currentState != "idle") m_animator->ChangeState("idle");
		str_currentState = "idle";
		break;
	case Action::Walk:
		if (str_currentState != "walk" && str_currentState != "Steal")
		{
			m_animator->ChangeState("walk");
		}
		str_currentState = "walk";
		break;
	case Action::Hit:
		break;
	case Action::Steal:
		if (str_currentState != "steal")m_animator->ChangeState("steal"); str_currentState = "steal";
		break;
	case Action::Dead:
		if (str_currentState != "dead")m_animator->ChangeState("dead"); str_currentState = "dead";
		break;
	}
}
