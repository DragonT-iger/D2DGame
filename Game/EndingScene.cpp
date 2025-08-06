#include "pch.h"
#include "EndingScene.h"
#include "GameManager.h"
#include "EndSceneManager.h"

void EndingScene::Awake()
{


	GameObject* gameManager = Instantiate("GameManager");
	gameManager->AddComponent<GameManager>();
	



	GameObject* endSceneManager = Instantiate("EndSceneManager");
	endSceneManager->AddComponent<EndSceneManager>();


	Scene::Awake();


}
