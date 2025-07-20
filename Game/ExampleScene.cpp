#include "pch.h"
#include "ExampleScene.h"
#include "PlayerController.h"

void ExampleScene::Awake()
{
	/* ********주의********
		Awake에서 Scene::Awake() 전에 게임오브젝트에다가 컴포넌트만 다셈 딴건 하지마샘
	*/


	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	// 할당 안돼서 assert 걸림
	
	m_player->AddComponent<PlayerController>();

	
	// 일단은 Awake에서 씬을 초기화하는 걸로
	// 씬은 게임오브젝트 초기화만 담당함	


	Scene::Awake();
}

