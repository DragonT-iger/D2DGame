#include "pch.h"
#include "ExampleScene.h"
#include "PlayerController.h"
#include "UITest.h"
#include "Crop.h"
#include "PlayerController_Sample.h"
#include "CinemachineCamera.h"
#include "GameObjectFindTest.h"
#include "SpawnManager.h"
#include "Farmer.h"

void ExampleScene::Awake()
{
	if(!IsActive())
		return;

	/* ********주의********
		Awake?�서 Scene::Awake() ?�에 게임?�브?�트?�다가 컴포?�트�??�셈 ?�건 ?��?마샘
	*/

	//m_slidebar = Instantiate("slidebar");
	//m_slidebar->AddComponent<Image>();	
	//m_slidebar->AddComponent<Slide_Bar>();
	//m_slidebar->AddComponent<UITest>();

	//m_slidebar->GetComponent<Transform>()->SetPosition({ 100, 150 });

	//m_slidebar->GetComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 160, 20 });

	//m_button = Instantiate("buttonTest");
	//m_button->GetComponent<Transform>()->SetPosition({100, 100});

	//m_button->AddComponent<Image>();
	//auto b = m_button->AddComponent<Button>();

	//auto b1 = ResourceManager::Instance().LoadTexture("button1_basic100.png");
	//auto b3 = ResourceManager::Instance().LoadTexture("button1_mouse_click.png");

	//b->AddEventSprite(b3, ButtonEvent::Idle);
	//b->AddEventSprite(b1, ButtonEvent::Highlight);
	//b->AddEventSprite(b3, ButtonEvent::Pressed);

	//SoundManager::Instance().Init();
	//SoundManager::Instance().BGM_Shot("sample_ten.wav");

	////m_button->GetComponent<Transform>()->Translate({ 100, 100 });

	m_background = Instantiate("background");

	m_spriteRenderer = m_background->AddComponent<SpriteRenderer>();

	m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("Test_back_02.png"));

	m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

	//m_player = Instantiate("Player");

	//m_player->SetTag("Player");

	//m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	//m_player->AddComponent<Animator>();
	//// ?�당 ?�돼??assert 걸림
	//
	//m_player->AddComponent<PlayerController_Sample>();

	//m_player->GetComponent<Transform>()->SetPosition({ 100.f, 100.f });

	//m_player->AddComponent<CircleCollider>();

	//b->AddPressEvent([this]() { m_slidebar->GetComponent<Slide_Bar>()->UpdateWidthRatio(1.0f); });
	//b->AddPressEvent([]() { std::cout << "버튼 ?��???" << std::endl; });

	/*GameObject* a = Instantiate("aa");

	SpriteRenderer* spriteRenderer = a->AddComponent<SpriteRenderer>();*/

	//ComPtr<ID2D1Bitmap1> bitmap;
	//bitmap = ResourceManager::Instance().LoadTexture("Player.png");
	//spriteRenderer->SetBitmap(bitmap);

	//spriteRenderer->SetSize(64.f, 64.f);

	m_player2 = Instantiate("Player2");
	m_player2->SetTag("Player2");

	m_spriteRenderer = m_player2->AddComponent<SpriteRenderer>();
	m_player2->AddComponent<Animator>();

	m_player2->GetComponent<Transform>()->SetScale({ 0.35, 0.35 });

	//m_spriteRenderer->SetOrderInLayer(2);

	PlayerController_Sample* pc = m_player2->AddComponent<PlayerController_Sample>();

	m_player2->AddComponent<BoxCollider>();

	pc->m_xSpeed = 350.f;
	pc->m_ySpeed = 350.f;


	m_farmer = Instantiate("Farmer");
	m_farmer->AddComponent<Farmer>();

	
	// ?�단?� Awake?�서 ?�을 초기?�하??걸로
	// ?��? 게임?�브?�트 초기?�만 ?�당??(?�스?�터 ?�각?�셈)


	Scene::Awake();
}


void ExampleScene::Start()
{

	// ?�확???�해?�이 start ?��? 마셈 가?�하�?Awake?�서 처리?�세??
	
	if (!IsActive())
		return;

	// 카메?�는 awake?�서 초기?�돼??그냥 ?�기???�음

	Camera* camera = GetCamera();
	
	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_player2);


	







	Scene::Start();
}
