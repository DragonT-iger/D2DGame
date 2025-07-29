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

	m_button = Instantiate(L"buttonTest");

	m_button->AddComponent<Image>();
	auto b = m_button->AddComponent<Button>();

	auto b1 = ResourceManager::Instance().LoadTexture("button1_basic100.png");
	auto b2 = ResourceManager::Instance().LoadTexture("button1_mouse_action.png");
	auto b3 = ResourceManager::Instance().LoadTexture("button1_mouse_click.png");

	b->AddEventSprite(b3, ButtonEvent::Idle);
	b->AddEventSprite(b1, ButtonEvent::Highlight);
	b->AddEventSprite(b3, ButtonEvent::Pressed);

	

	m_button->GetComponent<Transform>()->Translate({ 100, 100 });

	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	m_player->AddComponent<Animator>();
	// 할당 안돼서 assert 걸림
	
	m_player->AddComponent<PlayerController>();

	m_player->GetComponent<Transform>()->SetPosition({ 100.f, 100.f });

	m_player->AddComponent<BoxCollider>();

	b->AddPressEvent([this]() {m_player->GetComponent<Transform>()->Translate({ 20.f, 20.f }); });
	b->AddPressEvent([]() { std::cout << "버튼 눌렀음2" << std::endl; });

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

	m_player2->GetComponent<Transform>()->SetScale({ 2, 2 });

	m_spriteRenderer->SetOrderInLayer(2);

	PlayerController* pc = m_player2->AddComponent<PlayerController>();

	m_player2->AddComponent<BoxCollider>();

	pc->m_xSpeed = 175.f;
	pc->m_ySpeed = 175.f;

	
	// 일단은 Awake에서 씬을 초기화하는 걸로
	// 씬은 게임오브젝트 초기화만 담당함	(인스펙터 생각하셈)


	Scene::Awake();
}


void ExampleScene::Start()
{

	// 정확한 이해없이 start 쓰지 마셈 가능하면 Awake에서 처리하세요
	
	if (!IsActive())
		return;

	// 카메라는 awake에서 초기화돼서 그냥 여기서 적음

	Camera* camera = GetCamera();
	
	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_player2);











	Scene::Start();
}
