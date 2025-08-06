#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"
#include "EndingScene.h"
#include "InventorySlot.h"

int GameManager::ep_count = 0;
int GameManager::pt_count = 0;
int GameManager::pk_count = 0;
int GameManager::score = 0;


void GameManager::Awake()
{
}

void GameManager::Init()
{
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
	m_inventory = SceneManager::Instance().GetActiveScene()->FindGameObject("Inventory")->GetComponent<Inventory>();



}

void GameManager::OnInspectorGUI()
{
	static const char* kEndReasonStr[] = { "None", "BabyStarved", "PlayerDead", "Happy" };

	int current = static_cast<int>(m_endReason);
	if (ImGui::Combo("EndReason", &current, kEndReasonStr, IM_ARRAYSIZE(kEndReasonStr)))
		m_endReason = static_cast<EndReason>(current);
}

void GameManager::LoadEndingScene(EndReason reason)
{
	m_endReason = reason;
	SceneManager::Instance().LoadScene(std::unique_ptr<EndingScene>());
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

