#include "pch.h"
#include "EndingScene.h"
#include "GameManager.h"
#include "EndSceneManager.h"
#include "CinemachineCamera.h"
#include "TitleBtn.h"

void EndingScene::Awake()
{


	GameObject* gameManager = Instantiate("GameManager");
	auto gm = gameManager->AddComponent<GameManager>();
	
	GameObject* endSceneManager = Instantiate("EndSceneManager");
	endSceneManager->AddComponent<EndSceneManager>();




	GameObject* totalScore = Instantiate("Score");
	auto txt = totalScore->AddComponent<Text>();
	std::wstring score = L"Score : " + std::to_wstring(gm->GetTotalScore());
	txt->SetText(score, { 600, 200 }, L"Maplestory");
	txt->SetFontSize(70);
	totalScore->GetComponent<Transform>()->SetPosition({ 1100, 935 });


	GameObject* aliveTime = Instantiate("AliveTime");
	auto timetxt = aliveTime->AddComponent<Text>();
	int minuate = gm->GetAliveTime() / 60;
	int second = gm->GetAliveTime() % 60;

	std::wstring time;

	if (minuate >= 3)
	{
		time = L"";
	}
	else if (minuate != 0)
	{
		time  = L"Time: " + std::to_wstring(minuate) + L"m " + std::to_wstring(second) + L"s";
	}
	else
	{
		time = L"Time: " + std::to_wstring(second) + L"s";
	}
	
	
	timetxt->SetText(time, { 600, 200 }, L"Maplestory");
	timetxt->SetFontSize(70);
	aliveTime->GetComponent<Transform>()->SetPosition({ 1180, 865 });
	

	m_restart = Instantiate("restart");
	m_restart->AddComponent<Image>();
	auto btn = m_restart->AddComponent<Button>();
	m_restart->AddComponent<TitleBtn>();
	
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn5_Exit.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn5_Exit_Select.png"), ButtonEvent::Highlight);

	m_restart->GetComponent<Transform>()->SetPosition({ 1760, 995 });
	
	Scene::Awake();
}
