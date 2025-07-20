#include "pch.h"
#include "ExampleScene.h"
#include "PlayerController.h"

void ExampleScene::Awake()
{
	/* ********����********
		Awake���� Scene::Awake() ���� ���ӿ�����Ʈ���ٰ� ������Ʈ�� �ټ� ���� ��������
	*/


	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	// �Ҵ� �ȵż� assert �ɸ�
	
	m_player->AddComponent<PlayerController>();

	
	// �ϴ��� Awake���� ���� �ʱ�ȭ�ϴ� �ɷ�
	// ���� ���ӿ�����Ʈ �ʱ�ȭ�� �����	


	Scene::Awake();
}

