#include "pch.h"
#include "EndingScene.h"
#include "GameManager.h"
#include "EndSceneManager.h"
#include "CinemachineCamera.h"
#include "TitleBtn.h"

void EndingScene::Awake()
{


	GameObject* gameManager = Instantiate("GameManager");
	gameManager->AddComponent<GameManager>();
	



	GameObject* endSceneManager = Instantiate("EndSceneManager");
	endSceneManager->AddComponent<EndSceneManager>();

	m_restart = Instantiate("restart");
	m_restart->AddComponent<Image>();
	auto btn = m_restart->AddComponent<Button>();
	m_restart->AddComponent<TitleBtn>();
	
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn5_Exit.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn5_Exit_Select.png"), ButtonEvent::Highlight);

	m_restart->GetComponent<Transform>()->SetPosition({ 1760, 995 });
	
	
	Scene::Awake();
}
