#include "pch.h"
#include "MainScene.h"
#include "PlayerController.h"

void MainScene::Awake()
{
	/* ********����********
	
		������ ����Ŭ�� ���� �Ϻ����� ���� �����ٰ� ������ �ϸ� �ȵ� Mono���� ��� addcomponent �ؼ� ���� �־�� ����������Ŭ �׳��� ������



		��� : ���ӿ�����Ʈ���ٰ� ������Ʈ�� �ټ� ���� ��������
	*/


	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	// �Ҵ� �ȵż� assert �ɸ�
	
	m_player->AddComponent<PlayerController>();
	




	// ���� �� �����̶� awake�� �Ƚ��ְ� ���� ������ ����� ������ �ϴ� �𸣰��� �װ� ���� ã�ƺ��� �ҵ�
	
	


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
