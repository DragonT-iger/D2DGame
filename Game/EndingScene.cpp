#include "pch.h"
#include "EndingScene.h"
#include "GameManager.h"
#include "EndSceneManager.h"
#include "CinemachineCamera.h"
#include "EndingTitleBtn.h"

void EndingScene::Awake()
{
	

	GameObject* gameManager = Instantiate("GameManager");
	auto gm = gameManager->AddComponent<GameManager>();
	
	GameObject* endSceneManager = Instantiate("EndSceneManager");
	endSceneManager->AddComponent<EndSceneManager>();

	m_endingNum = Instantiate("EndingNum");
	auto img = m_endingNum->AddComponent<Image>();
	img->SetOrderInLayer(10);

	m_endingNum->GetComponent<Transform>()->SetPosition({ 400, 110 });

	GameObject* totalScore = Instantiate("Score");
	auto txt = totalScore->AddComponent<Text>();
	std::wstring score = L"Score : " + std::to_wstring(gm->GetTotalScore());
	txt->SetText(score, { 600, 200 }, L"Hakgyoansim Tuho");
	txt->SetFontSize(70);
	totalScore->GetComponent<Transform>()->SetPosition({ 1100, 935 });

	GameObject* aliveTime = Instantiate("AliveTime");
	auto timetxt = aliveTime->AddComponent<Text>();
	int minuate = (gm->GetAliveTime()-3) / 60;
	int second = (gm->GetAliveTime()-3) % 60;

	if (minuate < 0)
		minuate = 0;
	
	if (second < 0)
		second = 0;

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
	
	
	timetxt->SetText(time, { 600, 200 }, L"Hakgyoansim Tuho");
	timetxt->SetFontSize(70);
	aliveTime->GetComponent<Transform>()->SetPosition({ 1100, 865 });
	

	m_restart = Instantiate("restart");
	m_restart->AddComponent<Image>();
	auto btn = m_restart->AddComponent<Button>();
	m_restart->AddComponent<EndingTitleBtn>();
	
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("Btn_title.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("Btn_title_Selected.png"), ButtonEvent::Highlight);

	m_restart->GetComponent<Transform>()->SetPosition({ 1700, 960 });
	
	Scene::Awake();
}
