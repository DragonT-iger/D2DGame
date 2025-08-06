#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"


void GameManager::Init()
{
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
	m_inventory = SceneManager::Instance().GetActiveScene()->FindGameObject("Inventory")->GetComponent<Inventory>();
}

void GameManager::Update(float deltaTime)
{

}


