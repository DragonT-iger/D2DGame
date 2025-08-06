#include "pch.h"
#include "MainScene.h"
#include "Player.h"
#include "PlayerAnimator.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"
#include "Crop.h"
#include "Bush.h"
#include "FarmerManager.h"
#include "InventorySlot.h"
#include "Inventory.h"
#include "SpawnManager.h"
#include "PlayerSound.h"
#include "YSort.h"
#include "GameManager.h"
#include "Timer.h"
#include "HungryGauge.h"
#include "Baby.h"
#include "UI_Score.h"

void MainScene::Awake()
{
	if (!IsActive())
		return;

	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Light.ttf"), L"Maplestory");
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Bold.ttf"), L"Maplestory");

//Timer
	m_Timer = Instantiate("SceneTimer");
	m_Timer->AddComponent<Timer>();



//begin player-----
	player = Instantiate("Player");
	auto playerSR = player->AddComponent<SpriteRenderer>();
	player->AddComponent<BoxCollider>();
	player->AddComponent<Animator>();

	player->AddComponent<Player>();
	player->AddComponent<PlayerAnimator>();
	player->AddComponent<PlayerController>();
	player->AddComponent<PlayerSound>();
	player->AddComponent<YSort>()->SetStatic(false);
	player->GetComponent<Transform>()->SetScale({ 0.35f, 0.35f });
	player->AddComponent<Baby>();

	playerSR->SetOrderInLayer(1);

	m_hungryGauge = Instantiate("hungryGauge");
	m_hungryGauge->AddComponent<Image>();
	m_hungryGauge->AddComponent<Slide_Bar>();
	m_hungryGauge->AddComponent<HungryGauge>();
	m_hungryGauge->GetComponent<Transform>()->SetPosition({ 700, 800 });
	
//end player-----

////begin crop-----
//	crop = Instantiate("Crop");
//	crop->SetTag("crop");
//
//	crop->AddComponent<SpriteRenderer>();
//	crop->AddComponent<BoxCollider>();
//	crop->AddComponent<Animator>();
//	auto crop_scripts	= crop->AddComponent<Crop>();
//
//	crop->GetComponent<Transform>()->SetPosition(Vector2{0,0});
//	crop->GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });
//
//	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> cropbit = {
//		ResourceManager::Instance().LoadTexture("potatoL.png"),
//		ResourceManager::Instance().LoadTexture("potatoL.png"),
//		ResourceManager::Instance().LoadTexture("potatoL.png")
//	};
//
//	crop_scripts->SetCropData((FarmRank)0, (Crops)1, cropbit);
//
////end crop------

//begin message-----

	/*message = Instantiate("steal_message");

	auto message_render = message->AddComponent<SpriteRenderer>();
	message->GetComponent<Transform>()->SetParent(crop->GetComponent<Transform>());

	message->GetComponent<Transform>()->SetPosition(Vector2{ 0,250 });
	message->GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });

	message_render->SetBitmap(ResourceManager::Instance().LoadTexture("steal_message.png"));

	message->SetActive(false);*/
	

//end message-----

//begin Bush

	bush = Instantiate("Bush");
	bush->AddComponent<Bush>();
	bush->AddComponent<SpriteRenderer>();
	bush->AddComponent<BoxCollider>();
	bush->GetComponent<Transform>()->SetPosition(Vector2{ -100,0 });

//end Bush




	//Farmer

	//m_player2 = Instantiate("Player2");
	player->SetTag("Player"); //<<- �̰� ���ְ�

	SetPlayer(player); //<-- ���� ���� �˷��ְ�


	m_farmerManager = Instantiate("FarmerManager");
	m_farmerManager->AddComponent<FarmerManager>();


#pragma region SpawnManager,Inventory


	m_SpawnManager = Instantiate("SpawnManager");

	m_SpawnManager->AddComponent<SpawnManager>();

	m_inventory = Instantiate("Inventory");
	m_inventory->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("inventoryBG.png"), { 1200, 300 });
	m_inventory->AddComponent<Inventory>();
	m_inventory->GetComponent<Transform>()->SetPosition({ 960, 930 });

	m_slot1BG = Instantiate("Slot1BG");
	m_slot1BG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("inventorySlot.png"), { 350, 250 });
	m_slot1BG->GetComponent<Transform>()->SetPosition({ 550, 930 });

	m_slot2BG = Instantiate("Slot2BG");
	m_slot2BG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("inventorySlot.png"), { 350, 250 });
	m_slot2BG->GetComponent<Transform>()->SetPosition({ 950, 930 });

	m_slot3BG = Instantiate("Slot3BG");
	m_slot3BG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("inventorySlot.png"), { 350, 250 });
	m_slot3BG->GetComponent<Transform>()->SetPosition({ 1350, 930 });

	m_slot1 = Instantiate("Slot1");
	m_slot1->AddComponent<Image>();
	m_slot1->AddComponent<Slot>();
	m_slot1->GetComponent<Transform>()->SetPosition({ 550, 930 });
	m_slot1->GetComponent<Transform>()->SetParent(m_slot1BG->GetComponent<Transform>());
	m_slot1->AddComponent<Text>();

	m_slot2 = Instantiate("Slot2");
	m_slot2->AddComponent<Image>();
	m_slot2->AddComponent<Slot>();
	m_slot2->GetComponent<Transform>()->SetPosition({ 950, 930 });
	m_slot2->GetComponent<Transform>()->SetParent(m_slot2BG->GetComponent<Transform>());
	m_slot2->AddComponent<Text>();

	m_slot3 = Instantiate("Slot3");
	m_slot3->AddComponent<Image>();
	m_slot3->AddComponent<Slot>();
	m_slot3->GetComponent<Transform>()->SetPosition({ 1350, 930 });
	m_slot3->GetComponent<Transform>()->SetParent(m_slot3BG->GetComponent<Transform>());
	m_slot3->AddComponent<Text>();

	//SoundManager::Instance().BGM_Shot("sample_ten.wav");

	m_background = Instantiate("background");

	auto sr = m_background->AddComponent<SpriteRenderer>();

	sr->SetBitmap(ResourceManager::Instance().LoadTexture("Test_back_02.png"));
	sr->SetOrderInLayer(-200000);

	m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
#pragma endregion

	player->GetComponent<PlayerController>()->SetSpawnManager(m_SpawnManager->GetComponent<SpawnManager>());

#pragma  region SubMissionArea

	SubMissionArea1 = Instantiate("SubMissionArea1");
	SubMissionArea2 = Instantiate("SubMissionArea2");

	SubMissionArea1->SetTag("SubMissionArea");
	SubMissionArea2->SetTag("SubMissionArea");

	auto SMA1 = SubMissionArea1->AddComponent<BoxCollider>();
	auto SMA2 = SubMissionArea2->AddComponent<BoxCollider>();

	SMA1->SetSize(Vector2{ 521,4320 });
	SMA2->SetSize(Vector2{ 521,4320 });

	auto SAM1_T = SubMissionArea1->GetComponent<Transform>();
	auto SAM2_T = SubMissionArea2->GetComponent<Transform>();

	SAM1_T->SetPosition(Vector2{ 3580 ,0});
	SAM2_T->SetPosition(Vector2{ -3580,0 });


	GameManager::Instance().Init();

#pragma endregion

	Scene::Awake();
}

void MainScene::Start()
{
	if (!IsActive())
		return;

	Camera* cam = GetCamera();

	cam->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(player);

	//GameManager::Instance().Init();
	//스타트에 쓰지 말라고 3번말했다.

	Scene::Start();
}