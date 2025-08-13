#include "pch.h"
#include "Bush.h"
#include "YSort.h"

void Bush::Awake()
{
	m_transform = GetComponent<Transform>();
	//m_animator = GetComponent<Animator>();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
	GetOwner()->AddComponent<YSort>();

	m_boxCol = GetComponent<BoxCollider>();
}

void Bush::Start()
{
	GetOwner()->SetName("Bush");
	GetOwner()->SetTag("Bush");

	auto bush_sprite = ResourceManager::Instance().LoadTexture("bush_1.png");
	m_spriteRenderer->SetBitmap(bush_sprite);

	m_boxCol->SetSize(Vector2{ 100.f,36.f });
	m_boxCol->SetOffset({ 0, 30.f });
}

void Bush::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player"){
		m_spriteRenderer->SetOpacity(0.5f);
	}
}

void Bush::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {
		m_spriteRenderer->SetOpacity(1.f);
	}
}
