#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"
#include "EndingScene.h"


void GameManager::Init()
{
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
	m_inventory = SceneManager::Instance().GetActiveScene()->FindGameObject("Inventory")->GetComponent<Inventory>();
}

void GameManager::LoadEndingScene(EndReason reason)
{
	m_endReason = reason;
	SceneManager::Instance().LoadScene(std::unique_ptr<EndingScene>());
}

void GameManager::Update(float deltaTime)
{

}


