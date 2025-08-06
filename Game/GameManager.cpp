#include "pch.h"
#include "GameManager.h"

void GameManager::Awake()
{
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
}

void GameManager::Start()
{

}

void GameManager::Update(float deltaTime)
{
}

