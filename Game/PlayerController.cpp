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

	m_animator->AddClip("idle", moleIdle, true);
	m_animator->AddClip("walk", molewalk, true);
	m_animator->AddClip("hit", moleHit, false);
	m_animator->AddClip("steal", moleSteal, false);
	m_animator->AddClip("dead", moleDead, false);

	m_animator->SetEntryState("idle");

	auto collider = GetComponent<BoxCollider>();

	collider->SetSize({ 100, 100 });
	m_spriteRenderer->SetOpacity(1);
}

void PlayerController::Update(float deltaTime)
{
	int x = Input.GetAxisRaw("Horizontal");
	int y = Input.GetAxisRaw("Vertical");

	Vector2 dir{ (float)x,(float)y };

	m_transform->Translate(dir * m_Spd * deltaTime);

}
