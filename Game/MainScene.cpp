#include "pch.h"
#include "MainScene.h"
#include "PlayerController.h"

void MainScene::Awake()
{
	/* ********주의********
	
		라이프 사이클이 아직 완벽하지 않음 씬에다가 적을라 하면 안됨 Mono에서 적어서 addcomponent 해서 씬에 넣어야 라이프사이클 그나마 덜꼬임



		요약 : 게임오브젝트에다가 컴포넌트만 다셈 딴건 하지마샘
	*/


	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	// 할당 안돼서 assert 걸림
	
	m_player->AddComponent<PlayerController>();
	




	// 뭔가 얼리 리턴이랑 awake를 안써주고 싶은 구조로 만들고 싶지만 일단 모르겠음 그건 좀더 찾아봐야 할듯
	
	


	Scene::Awake();
}


void MainScene::Start()
{


	Scene::Start();
}



void MainScene::Update(float deltaTime)
{




	Scene::Update(deltaTime);
}
