#include "pch.h"
#include "Text.h"

void Text::Awake()
{
	m_transform = GetComponent<Transform>();
}

void Text::Start()
{
}

void Text::Update(float deltaTime)
{
	m_renderInfo.m_destRect = { -(m_size.width / 2) + m_transform->GetPosition().x, -(m_size.height / 2) + m_transform->GetPosition().y,
								(m_size.width / 2) + m_transform->GetPosition().x,  (m_size.height / 2) + m_transform->GetPosition().y };
}
