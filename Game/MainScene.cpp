#include "pch.h"
#include "MainScene.h"

void MainScene::Awake()
{
	if(this->IsActive() == false)
		return;
	


	GameObject* player = CreateGameObject(L"Player");

	player->SetTag(L"Player");

	SpriteRenderer* spriteRenderer = player->AddComponent<SpriteRenderer>();
	// �Ҵ� �ȵż� assert �ɸ�


	//ID2D1Bitmap* bitmap = ResourceManager::GetInstance()->GetBitmap(L"Player.png");

	//spriteRenderer->SetBitmap()


	// ���� �� �����̶� awake�� �Ƚ��ְ� ���� ������ ����� ������ �ϴ� �𸣰��� �װ� ���� ã�ƺ��� �ҵ�
	
	


	Scene::Awake();
}
