#include "pch.h"
#include "PlayerController.h"

enum class Action
{
	Idle,
	Walk,
	Hit,
	Steal,
	Alive,
	Dead
};

enum class Visibilty
{
	Hide,
	Visible
};

//enum class State
//{
//	Alive,
//	Dead
//};

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

	m_animator->AddClip("idle", moleIdle);
	m_animator->AddClip("walk", molewalk);
	m_animator->AddClip("hit", moleHit);
	m_animator->AddClip("steal", moleSteal);
	m_animator->AddClip("dead", moleDead);

	auto collider = GetComponent<BoxCollider>();

	collider->SetSize({ 100, 100 });
	m_spriteRenderer->SetOpacity(1);
}

void PlayerController::Update(float deltaTime)
{
	Action a = Action::Idle;

	if (Input.GetKeyDown(Keycode::UP))			{ a = Action::Walk; m_transform->Translate(0, m_Spd_Y * deltaTime); }
	else if (Input.GetKeyDown(Keycode::DOWN))	{ a = Action::Walk; m_transform->Translate(0, -m_Spd_Y * deltaTime); }
	else if (Input.GetKeyDown(Keycode::LEFT))  { a = Action::Walk; m_transform->Translate(-m_Spd_X * deltaTime, 0); if (!m_spriteRenderer->IsFlip()) m_spriteRenderer->SetFlip(true); }
	else if (Input.GetKeyDown(Keycode::RIGHT))  { a = Action::Walk; m_transform->Translate(m_Spd_X * deltaTime, 0); if(m_spriteRenderer->IsFlip()) m_spriteRenderer->SetFlip(false); }
	else if (Input.GetKeyDown(Keycode::Z))		{ a = Action::Steal; }
	else if (Input.GetKeyDown(Keycode::Q))		{ a = Action::Dead; }
	else if (Input.GetKeyDown(Keycode::W))		 { a = Action::Hit; }


	switch (a)
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
		break;
	case Action::Dead:
		break;
	default:
		break;
	}
}
