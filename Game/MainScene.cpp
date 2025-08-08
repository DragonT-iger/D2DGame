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
#include "SubMissionArea.h"

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

	//player->GetComponent<Transform>()->SetPosition({ 500.f , 500.f });
	player->AddComponent<Baby>();

	playerSR->SetOrderInLayer(1);

	
	
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
	m_inventory->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Main_Panel.png"), { 1030, 250 });
	m_inventory->AddComponent<Inventory>();
	m_inventory->GetComponent<Transform>()->SetPosition({ 960, 930 });

	m_slot1BG = Instantiate("Slot1BG");
	auto Img = m_slot1BG->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Frame.png"), { 160, 160 });
	m_slot1BG->GetComponent<Transform>()->SetPosition({ 1010, 930 });

	m_slot2BG = Instantiate("Slot2BG");
	m_slot2BG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Frame.png"), { 160, 160 });
	m_slot2BG->GetComponent<Transform>()->SetPosition({ 1190, 930 });

	m_slot3BG = Instantiate("Slot3BG");
	m_slot3BG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Frame.png"), { 160, 160 });
	m_slot3BG->GetComponent<Transform>()->SetPosition({ 1370, 930 });

	m_slot1 = Instantiate("Slot1");
	m_slot1Text = Instantiate("Slot1Text");
	m_slot1->AddComponent<Image>();
	auto slot = m_slot1->AddComponent<Slot>();
	m_slot1->GetComponent<Transform>()->SetPosition({ 1010, 930 });
	m_slot1->GetComponent<Transform>()->SetParent(m_slot1BG->GetComponent<Transform>());
	auto txt = m_slot1Text->AddComponent<Text>();
	m_slot1Text->GetComponent<Transform>()->SetPosition({ 1045, 960 });
	slot->RegisterText(txt);

	m_slot2 = Instantiate("Slot2");
	m_slot2Text = Instantiate("Slot2Text");
	m_slot2->AddComponent<Image>();
	slot = m_slot2->AddComponent<Slot>();
	m_slot2->GetComponent<Transform>()->SetPosition({ 1190, 930 });
	m_slot2->GetComponent<Transform>()->SetParent(m_slot2BG->GetComponent<Transform>());
	txt = m_slot2Text->AddComponent<Text>();
	m_slot2Text->GetComponent<Transform>()->SetPosition({ 1225, 960 });
	slot->RegisterText(txt);

	m_slot3 = Instantiate("Slot3");
	m_slot3Text = Instantiate("Slot3Text");
	m_slot3->AddComponent<Image>();
	slot = m_slot3->AddComponent<Slot>();
	m_slot3->GetComponent<Transform>()->SetPosition({ 1370, 930 });
	m_slot3->GetComponent<Transform>()->SetParent(m_slot3BG->GetComponent<Transform>());
	txt = m_slot3Text->AddComponent<Text>();
	m_slot3Text->GetComponent<Transform>()->SetPosition({ 1405, 960 });
	slot->RegisterText(txt);

	//SoundManager::Instance().BGM_Shot("sample_ten.wav");

	m_background = Instantiate("background");

	auto sr = m_background->AddComponent<SpriteRenderer>();

	sr->SetBitmap(ResourceManager::Instance().LoadTexture("background_test_1.png"));
	sr->SetOrderInLayer(-200000);

	m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });
#pragma endregion

#pragma region UI

	m_profile = Instantiate("playerProfile");
	m_profileBG = Instantiate("playerProfileBG");
	m_babyprofile = Instantiate("babyProfile");
	m_babyprofileBG = Instantiate("babyProfileBG");

	m_hungryBG = Instantiate("hungryBG");
	m_hungryGauge = Instantiate("hungryGauge");
	m_hungryImage = Instantiate("hungryImg");

	m_hp1 = Instantiate("hp1");
	m_hp2 = Instantiate("hp2");
	m_hp3 = Instantiate("hp3");

	m_profileBG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Paper_Frame.png"), { 110, 110 });
	m_babyprofileBG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Paper_Frame.png"), { 110, 110 });
	m_profileBG->GetComponent<Transform>()->SetPosition({ 550, 875 });
	m_babyprofileBG->GetComponent<Transform>()->SetPosition({ 550, 985 });

	m_hp1->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Heart.png"), { 72, 65 });
	m_hp1->GetComponent<Transform>()->SetPosition({ 685, 980 });
	m_hp2->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Heart.png"), { 72, 65 });
	m_hp2->GetComponent<Transform>()->SetPosition({ 770, 980 });
	m_hp3->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Heart.png"), { 72, 65 });
	m_hp3->GetComponent<Transform>()->SetPosition({ 855, 980 });

	m_hungryGauge->AddComponent<Image>();
	m_hungryGauge->AddComponent<Slide_Bar>();
	m_hungryGauge->AddComponent<HungryGauge>();
	m_hungryGauge->GetComponent<Transform>()->SetPosition({ 770, 880 });

#pragma endregion

	player->GetComponent<PlayerController>()->SetSpawnManager(m_SpawnManager->GetComponent<SpawnManager>());

#pragma  region SubMissionArea

	SubMissionArea1 = Instantiate("SubMissionArea1");
	SubMissionArea2 = Instantiate("SubMissionArea2");

	SubMissionArea1->SetTag("SubMissionArea");
	SubMissionArea2->SetTag("SubMissionArea");

	SubMissionArea1->AddComponent<SubMissionArea>();
	SubMissionArea2->AddComponent<SubMissionArea>();

	auto sub_box1 = SubMissionArea1->AddComponent<BoxCollider>();
	auto sub_box2 = SubMissionArea2->AddComponent<BoxCollider>();

	auto SAM1_T = SubMissionArea1->GetComponent<Transform>();
	auto SAM2_T = SubMissionArea2->GetComponent<Transform>();

	SAM1_T->SetPosition(Vector2{ 3580 ,0 });
	SAM2_T->SetPosition(Vector2{ -3580,0 });

#pragma endregion

#pragma region Score

	ui_score = Instantiate("UI_Score");
	ui_score->AddComponent<UI_Score>();
	ui_score->AddComponent<Text>();
	ui_score->AddComponent<Image>();
	ui_score->GetComponent<Transform>()->SetPosition(Vector2{ 1770,25 });

#pragma endregion

	GameManager::Instance().Init(); //player랑 inventory 연결.
	Scene::Awake();
}

void MainScene::Start()
{
	if (!IsActive())
		return;

	Camera* cam = GetCamera();

	cam->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(player);

	Scene::Start();
}