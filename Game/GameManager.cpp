#include "pch.h"
#include "GameManager.h"
#include "Inventory.h"
#include "EndingScene.h"
#include "Player.h"
#include "PlayerController.h"
#include "PlayerAnimator.h"
#include "CinemachineCamera.h"
#include "InventorySlot.h"
#include "ClientSceneManager.h"

int GameManager::ep_count = 0;
int GameManager::pt_count = 0;
int GameManager::pk_count = 0;
int GameManager::totalscore = 0;




void GameManager::Update(float deltaTime)
{
	inGameTime += deltaTime;

	if (inGameTime >= 60.0f && inGameTime <= 60.1f)
	{
		m_player->GetComponent<Player>()->SetDecreaseFull(3.f);
	}
		
	

	CountThree();
	if(m_GameState == GameState::Main)
	CheckHappyEnd();
}

void GameManager::Init()
{
	totalscore = 0;
	inGameTime = 0.f;
	countThree = 2;
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
	m_inventory = SceneManager::Instance().GetActiveScene()->FindGameObject("Inventory")->GetComponent<Inventory>();

	if (m_text)
	{
		m_text->GetOwner()->SetActive(true);
		m_text->SetText(L"3", { 300, 300 }, L"Hakgyoansim Tuho");
	}
}
void GameManager::OnInspectorGUI()
{
	static const char* kEndReasonStr[] = { "None", "BabyStarved", "PlayerDead", "Happy" };

	int current = static_cast<int>(m_endReason);
	if (ImGui::Combo("EndReason", &current, kEndReasonStr, IM_ARRAYSIZE(kEndReasonStr)))
		m_endReason = static_cast<EndReason>(current);

	//bool full = m_isFullscreen;
	//if (ImGui::Checkbox("Fullscreen", &full))
	//{
	//	m_isFullscreen = full;
	//	SetFullScreen(m_isFullscreen);
	//}
}

void GameManager::SetFullScreen(bool isFull)
{
	D2DRenderer::Instance().SetFullscreen(isFull);
}

void GameManager::LoadEndingScene(EndReason reason)
{
	m_endReason = reason;
	ClientSceneManager::Instance().LoadScene(std::make_unique<EndingScene>());
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

	curScore = (temp_ep * 150) + (temp_pt * 70) + (temp_pk * 400);


	totalscore += curScore;

	return curScore;
}

void GameManager::AddScore(int num)
{
	totalscore += num;
}

void GameManager::CheckHappyEnd()
{
	if (EndTime < inGameTime)
	{
		m_player->GetComponent<Player>()->PlayClear();

		if(!m_player->GetComponent<Player>()->PlayClear())
			LoadEndingScene(EndReason::Happy);
	}
}

void GameManager::CountThree()
{
	if (m_GameState != GameState::Main) return;
	//Á¤Áö
	if (countThree > 2) return;
		
	if (countThree  != static_cast<int>(inGameTime) && m_text)
	{
		countThree = static_cast<int>(inGameTime);
		if (countThree > 2)
		{
			m_text->GetOwner()->SetActive(false);
			auto p_Component = m_player->GetComponent<Player>();
			auto p_Controller = m_player->GetComponent<PlayerController>();

			p_Component->SetActive(true);
			p_Controller->SetActive(true);
			return;
		}
		else
		{
			m_text->SetText(std::to_wstring(3 - countThree), { 300, 300 }, L"Hakgyoansim Tuho");
		}
	}
}

