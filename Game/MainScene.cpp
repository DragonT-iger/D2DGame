#include "pch.h"
#include "MainScene.h"

void MainScene::Awake()
{
	if(this->IsActive() == false)
		return;
	


	GameObject* player = CreateGameObject(L"Player");

	player->SetTag(L"Player");

	SpriteRenderer* spriteRenderer = player->AddComponent<SpriteRenderer>();
	// 할당 안돼서 assert 걸림


	//ID2D1Bitmap* bitmap = ResourceManager::GetInstance()->GetBitmap(L"Player.png");

	//spriteRenderer->SetBitmap()


	// 뭔가 얼리 리턴이랑 awake를 안써주고 싶은 구조로 만들고 싶지만 일단 모르겠음 그건 좀더 찾아봐야 할듯
	
	


	Scene::Awake();
}
