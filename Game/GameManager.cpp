#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"
#include "InventorySlot.h"

int GameManager::ep_count = 0;
int GameManager::pt_count = 0;
int GameManager::pk_count = 0;
int GameManager::score = 0;

void GameManager::Init()
{
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
	m_inventory = SceneManager::Instance().GetActiveScene()->FindGameObject("Inventory")->GetComponent<Inventory>();
}

int GameManager::ReceiveScore(const std::vector<SlotData>& data)
{
	int curScore = 0;

	for (auto& cd : data)
	{
		switch (cd.type)
		{
		case Eggplant:
			ep_count += cd.count;
			break;
		case Potato:
			pt_count += cd.count;
			break;
		case Pumpkin:
			pk_count += cd.count;
			break;
		}
	}

	curScore = (ep_count * 25) + (pt_count * 10) + (pk_count * 50);

	score += curScore;

	return curScore;

}

void GameManager::Update(float deltaTime)
{

}


