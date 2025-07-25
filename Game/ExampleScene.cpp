#include "pch.h"
#include "ExampleScene.h"
#include "PlayerController.h"

void ExampleScene::Awake()
{
	if(!IsActive())
		return;

	/* ********����********
		Awake���� Scene::Awake() ���� ���ӿ�����Ʈ���ٰ� ������Ʈ�� �ټ� ���� ��������
	*/

	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	m_player->AddComponent<Animator>();
	// �Ҵ� �ȵż� assert �ɸ�
	
	m_player->AddComponent<PlayerController>();

	m_player->GetComponent<Transform>()->SetPosition({ 100.f, 100.f });

	m_player->AddComponent<CircleCollider>();

	GameObject* a = Instantiate(L"aa");

	SpriteRenderer* spriteRenderer = a->AddComponent<SpriteRenderer>();

	ComPtr<ID2D1Bitmap1> bitmap;
	bitmap = ResourceManager::Instance().LoadTexture("Player.png");
	spriteRenderer->SetBitmap(bitmap);

	spriteRenderer->SetSize(64.f, 64.f);


	m_player2 = Instantiate(L"Player2");
	m_player2->SetTag(L"Player2");

	m_spriteRenderer = m_player2->AddComponent<SpriteRenderer>();
	m_player2->AddComponent<Animator>();

	PlayerController* pc = m_player2->AddComponent<PlayerController>();

	m_player2->AddComponent<CircleCollider>();

	pc->m_xSpeed = 75.f;
	pc->m_ySpeed = 75.f;



	
	// �ϴ��� Awake���� ���� �ʱ�ȭ�ϴ� �ɷ�
	// ���� ���ӿ�����Ʈ �ʱ�ȭ�� �����	(�ν����� �����ϼ�)


	Scene::Awake();
}

