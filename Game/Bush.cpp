#include "pch.h"
#include "Bush.h"
#include "YSort.h"

void Bush::Awake()
{
	m_transform = GetComponent<Transform>();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
	m_animator = GetComponent<Animator>();
	GetOwner()->AddComponent<YSort>();

	auto bush_swing = ResourceManager::Instance().LoadAnimationClip("bush_three_2.json", "three_bush_swing");
	m_animator->AddClip("bush_swing", bush_swing, false);
	m_animator->SetEntryState("bush_swing");

	m_boxCol = GetComponent<BoxCollider>();
}

void Bush::Start()
{
	GetOwner()->SetName("Bush");
	GetOwner()->SetTag("Bush");

	auto bush_sprite = ResourceManager::Instance().LoadTexture("bush_1.png");
	//m_spriteRenderer->SetBitmap(bush_sprite);

	m_boxCol->SetSize(Vector2{ 500.0f,36.f });
	m_boxCol->SetOffset({ 0, 30.f });
}

void Bush::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
	{
		if (m_animator->GetCurState() == "bush_swing")
		{
			m_animator->ChangeState("bush_swing");
		}
		
		m_spriteRenderer->SetOpacity(0.5f);
	}
}

void Bush::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
	{
		if (m_animator->GetCurState() == "bush_swing")
		{
			m_animator->ChangeState("bush_swing");
		}
		m_spriteRenderer->SetOpacity(1.f);
	}
}
