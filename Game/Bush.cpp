#include "pch.h"
#include "Bush.h"

void Bush::Awake()
{
	m_transform = GetComponent<Transform>();
	//m_animator = GetComponent<Animator>();
	m_spriteRenderer = GetComponent<SpriteRenderer>();

	m_boxCol = GetComponent<BoxCollider>();
}

void Bush::Start()
{
	GetOwner()->SetName("Bush");
	GetOwner()->SetTag("Bush");

	auto bush_sprite = ResourceManager::Instance().LoadTexture("bush_1.png");
	m_spriteRenderer->SetBitmap(bush_sprite);

	m_boxCol->SetSize(Vector2{ 200,200 });
}

void Bush::OnTriggerEnter(Collider* other)
{
	m_spriteRenderer->SetOpacity(0.7f);
}

void Bush::OnTriggerExit(Collider* other)
{
	m_spriteRenderer->SetOpacity(1);
}
