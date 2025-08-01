#include "pch.h"
#include "PlayerController.h"

void PlayerController::Awake()
{
	m_transform = GetComponent<Transform>();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
	m_animator = GetComponent<Animator>();

	str_currentState = "idle";
}

void PlayerController::Start()
{
	auto moleIdle = ResourceManager::Instance().LoadAnimationClip( "mole_final.json", "idle");
	auto molewalk = ResourceManager::Instance().LoadAnimationClip( "mole_final.json", "walk");
	auto moleHit = ResourceManager::Instance().LoadAnimationClip(  "mole_final.json", "hit");
	auto moleSteal = ResourceManager::Instance().LoadAnimationClip("mole_final.json", "steal");
	auto moleDead = ResourceManager::Instance().LoadAnimationClip( "mole_final.json", "dead");

	m_animator->AddClip("idle", moleIdle, true);
	m_animator->AddClip("walk", molewalk, true);
	m_animator->AddClip("hit", moleHit, false);
	m_animator->AddClip("steal", moleSteal, false);
	m_animator->AddClip("dead", moleDead, false);

	m_animator->SetEntryState("idle");

	auto collider = GetComponent<BoxCollider>();
	collider->SetSize({ 100, 100 });
	m_spriteRenderer->SetOpacity(1);

	message = message->Find("steal_message");
}

void PlayerController::Update(float deltaTime)
{
	if (state == State::Alive)
	{
		int x = Input.GetAxisRaw("Horizontal");
		int y = Input.GetAxisRaw("Vertical");
		Vector2 dir{ (float)x,(float)y };
		dir.Normalize();

		if (action == Action::Idle || action == Action::Walk)
		{
			if (x < 0) { m_spriteRenderer->SetFlip(true); }
			else if (x > 0) { m_spriteRenderer->SetFlip(false); }
		}
		
		if (Input.GetKeyDown(Keycode::B)) { action = Action::Hit; }
		if (Input.GetKeyDown(Keycode::N)) { m_animator->ChangeState("dead"); state = State::Dead; return; }
		

		switch (action)
		{
		case Action::Idle:
			if (dir != Vector2{ 0,0 })
			{
				m_animator->ChangeState("walk");
				action = Action::Walk;
				break;
			}
			else if (m_animator->GetCurState() != "idle")
			{
				m_animator->ChangeState("idle");
				action = Action::Idle;
			}
			break;
		case Action::Walk:
			if (dir == Vector2{ 0,0 })
			{
				m_animator->ChangeState("idle");
				action = Action::Idle;
				break;
			}
			m_transform->Translate(dir * m_Spd * deltaTime);
			break;
		case Action::Hit:
			if (m_animator->GetCurState() != "hit")
			{
				m_animator->ChangeState("hit");
			}
			if (m_animator->IsAnimeEnd())
			{
				action = Action::Idle;
			}
			break;
		case Action::Steal:
			if (m_animator->GetCurState() != "steal")
			{
				m_animator->ChangeState("steal");
			}
			if (m_animator->IsAnimeEnd())
			{
				action = Action::Idle;
			}
			break;
		}
	}

}

void PlayerController::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "crop")
	{
		message->SetActive(true);
	}
}

void PlayerController::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "crop")
	{
		if (Input.GetKeyDown(Keycode::Z)) { action = Action::Steal; }
	}
}

void PlayerController::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "crop")
	{
		message->SetActive(false);
	}
}
