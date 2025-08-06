#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"
#include "EndingScene.h"
#include "InventorySlot.h"

int GameManager::ep_count = 0;
int GameManager::pt_count = 0;
int GameManager::pk_count = 0;
int GameManager::totalscore = 0;

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

int GameManager::ReceiveScore(const std::vector<SlotData>& data)
{
	int curScore = 0;

	int temp_ep = 0;
	int temp_pt = 0;
	int temp_pk = 0;

	for (auto& cd : data)
	{
		switch (cd.type)
		{
		case Eggplant:
			ep_count += cd.count;
			temp_ep = cd.count;
			break;
		case Potato:
			pt_count += cd.count;
			temp_pt = cd.count;
			break;
		case Pumpkin:
			pk_count += cd.count;
			temp_pk = cd.count;
			break;
		}
	}

	curScore = (temp_ep * 25) + (temp_pt * 10) + (temp_pk * 50);


	totalscore += curScore;

	return curScore;

}

