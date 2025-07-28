#include "pch.h"
#include "ExampleScene.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"

void ExampleScene::Awake()
{
	if(!IsActive())
		return;

	/* ********주의********
		Awake에서 Scene::Awake() 전에 게임오브젝트에다가 컴포넌트만 다셈 딴건 하지마샘
	*/

	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	m_player->AddComponent<Animator>();
	// 할당 안돼서 assert 걸림
	
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

	pc->m_xSpeed = 175.f;
	pc->m_ySpeed = 175.f;

	
	// 일단은 Awake에서 씬을 초기화하는 걸로
	// 씬은 게임오브젝트 초기화만 담당함	(인스펙터 생각하셈)


	Scene::Awake();
}


void ExampleScene::Start()
{

	
	if (!IsActive())
		return;

	// 카메라는 awake에서 초기화돼서 그냥 여기서 적음

	Camera* camera = GetCamera();
	
	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_player2);











	Scene::Start();
}
