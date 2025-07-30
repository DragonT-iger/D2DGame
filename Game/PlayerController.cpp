#include "pch.h"
#include "PlayerController.h"

void PlayerController::Awake()
{
	m_transform      = GetComponent<Transform>();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
	m_animator		 = GetComponent<Animator>();
}

void PlayerController::Start()
{

}

void PlayerController::Update(float deltaTime)
{

}
