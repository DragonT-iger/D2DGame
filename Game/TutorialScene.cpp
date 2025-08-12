#include "pch.h"
#include "TutorialScene.h"
#include "Player.h"
#include "PlayerAnimator.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"
#include "Crop.h"
#include "Bush.h"
#include "FarmerManager.h"
#include "InventorySlot.h"
#include "Inventory.h"
#include "PlayerSound.h"
#include "YSort.h"
#include "GameManager.h"
#include "HungryGauge.h"
#include "Baby.h"
#include "UI_Score.h"
#include "SubMissionArea.h"
#include "EscBtn.h"
#include "TitleBtn.h"
#include "SkipButton.h"
#include "SettingButton.h"
#include "AcceptSetting.h"
#include "QuitSetting.h"
#include "Farmer.h"
#include "SpawnManager.h"
#include "Timer.h"

void TutorialScene::Awake()
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
	BoxCollider* boxcol = player->AddComponent<BoxCollider>();
	player->AddComponent<Animator>();
		
	player->AddComponent<Player>();
	player->AddComponent<PlayerAnimator>();
	player->AddComponent<PlayerController>();
	player->AddComponent<PlayerSound>();
	player->AddComponent<YSort>()->SetStatic(false);
	player->GetComponent<Transform>()->SetScale({ 0.35f, 0.35f });

	player->GetComponent<Transform>()->SetPosition({ -3560.0f , 0 });
	//player->AddComponent<Baby>();

	playerSR->SetOrderInLayer(1);

	//m_farmerHouse = Instantiate("House");
	//m_farmerHouse->SetTag("House");
	//auto sr = m_farmerHouse->AddComponent<SpriteRenderer>();
	//sr->SetBitmap(ResourceManager::Instance().LoadTexture("farmer_house_test_1.png"));
	//auto box = m_farmerHouse->AddComponent<BoxCollider>();
	//m_farmerHouse->AddComponent<YSort>(140);
	//m_farmerHouse->GetComponent<Transform>()->SetPosition({ 0, 0 });
	//m_farmerHouse->GetComponent<Transform>()->SetScale({ 0.6, 0.6 });
	//box->SetSize({ 300, 270 });
	//box->SetOffset({ 0, -160 });
	
	
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

#pragma region bush

	//bush1 = Instantiate("Bush1");
	//bush1->AddComponent<Bush>();
	//bush1->AddComponent<SpriteRenderer>();
	//bush1->AddComponent<BoxCollider>();

	bush2 = Instantiate("Bush2");
	bush2->AddComponent<Bush>();
	bush2->AddComponent<SpriteRenderer>();
	bush2->AddComponent<BoxCollider>();

	bush3 = Instantiate("Bush3");
	bush3->AddComponent<Bush>();
	bush3->AddComponent<SpriteRenderer>();
	bush3->AddComponent<BoxCollider>();

	bush4 = Instantiate("Bush4");
	bush4->AddComponent<Bush>();
	bush4->AddComponent<SpriteRenderer>();
	bush4->AddComponent<BoxCollider>();

	bush5 = Instantiate("Bush5");
	bush5->AddComponent<Bush>();
	bush5->AddComponent<SpriteRenderer>();
	bush5->AddComponent<BoxCollider>();

	bush6 = Instantiate("Bush6");
	bush6->AddComponent<Bush>();
	bush6->AddComponent<SpriteRenderer>();
	bush6->AddComponent<BoxCollider>();

	//bush1->GetComponent<Transform>()->SetPosition(Vector2{ -300, 200 });
	bush2->GetComponent<Transform>()->SetPosition(Vector2{ -400, 200 });
	bush3->GetComponent<Transform>()->SetPosition(Vector2{ -200, 200 });
	bush4->GetComponent<Transform>()->SetPosition(Vector2{ 0, 200 });
	bush5->GetComponent<Transform>()->SetPosition(Vector2{ 200, 200 });
	bush6->GetComponent<Transform>()->SetPosition(Vector2{ 400, 200 });

	//bush1->GetComponent<Transform>()->SetScale(Vector2{ 0.35, 0.35 });;
	bush2->GetComponent<Transform>()->SetScale(Vector2{ 0.35, 0.35 });;
	bush3->GetComponent<Transform>()->SetScale(Vector2{ 0.35, 0.35 });;
	bush4->GetComponent<Transform>()->SetScale(Vector2{ 0.35, 0.35 });;
	bush5->GetComponent<Transform>()->SetScale(Vector2{ 0.35, 0.35 });;
	bush6->GetComponent<Transform>()->SetScale(Vector2{ 0.35, 0.35 });;

	bush4->GetComponent<BoxCollider>()->SetSize({1300.f, 200.f});

#pragma endregion

//end Bush
	//Farmer

	//m_player2 = Instantiate("Player2");
	player->SetTag("Player"); //<<- ï¿½Ì°ï¿½ ï¿½ï¿½ï¿½Ö°ï¿½

	SetPlayer(player); //<-- ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ë·ï¿½ï¿½Ö°ï¿½


	//m_farmerManager = Instantiate("FarmerManager");
	//m_farmerManager->AddComponent<FarmerManager>();

	GameObject* farmer = Instantiate("Farmer");
	Farmer* fm = farmer->AddComponent<Farmer>();



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

	m_slot1Full = Instantiate("Slot1Full");
	slot->RegisterFullImage(m_slot1Full->AddComponent<Image>());

	m_slot2 = Instantiate("Slot2");
	m_slot2Text = Instantiate("Slot2Text");
	m_slot2->AddComponent<Image>();
	slot = m_slot2->AddComponent<Slot>();
	m_slot2->GetComponent<Transform>()->SetPosition({ 1190, 930 });
	m_slot2->GetComponent<Transform>()->SetParent(m_slot2BG->GetComponent<Transform>());
	txt = m_slot2Text->AddComponent<Text>();
	m_slot2Text->GetComponent<Transform>()->SetPosition({ 1225, 960 });
	slot->RegisterText(txt);

	m_slot2Full = Instantiate("Slot1Full");
	slot->RegisterFullImage(m_slot2Full->AddComponent<Image>());

	m_slot3 = Instantiate("Slot3");
	m_slot3Text = Instantiate("Slot3Text");
	m_slot3->AddComponent<Image>();
	slot = m_slot3->AddComponent<Slot>();
	m_slot3->GetComponent<Transform>()->SetPosition({ 1370, 930 });
	m_slot3->GetComponent<Transform>()->SetParent(m_slot3BG->GetComponent<Transform>());
	txt = m_slot3Text->AddComponent<Text>();
	m_slot3Text->GetComponent<Transform>()->SetPosition({ 1405, 960 });
	slot->RegisterText(txt);

	m_slot3Full = Instantiate("Slot1Full");
	slot->RegisterFullImage(m_slot3Full->AddComponent<Image>());

	//SoundManager::Instance().BGM_Shot("sample_ten.wav");

	
#pragma endregion

	m_background = Instantiate("TutorialBackground");

	SpriteRenderer* spriteRenderer = m_background->AddComponent<SpriteRenderer>();

	spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("TutorialBackground.png"));
	spriteRenderer->SetOrderInLayer(-200000);

	m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

#ifdef _DEBUG
	//?”ë²„ê·¸ìš©
	m_areaBox1 = Instantiate("debugBox1");
	m_areaBox2 = Instantiate("debugBox2");
	m_areaBox3 = Instantiate("debugBox3");
	m_areaBoxHouse = Instantiate("HouseBox");

	auto col = m_areaBox1->AddComponent<BoxCollider>();
	col->SetSize({ 2140, 1440 });
	col = m_areaBox2->AddComponent<BoxCollider>();
	col->SetSize({ 4160, 2660 });
	col = m_areaBox3->AddComponent<BoxCollider>();
	col->SetSize({ 6420, 4220 });
	col = m_areaBoxHouse->AddComponent<BoxCollider>();
	col->SetSize({ 470, 355 });
#endif


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

	Img = m_profileBG->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Paper_Frame.png"), { 110, 110 });
	Img->SetOrderInLayer(6);
	Img = m_babyprofileBG->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Paper_Frame.png"), { 110, 110 });
	Img->SetOrderInLayer(6);
	m_babyprofileBG->GetComponent<Transform>()->SetPosition({ 550, 875 });
	m_profileBG->GetComponent<Transform>()->SetPosition({ 550, 985 });

	Img = m_profile->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("mom_profile1.png"), { 80, 80 });
	Img->SetOrderInLayer(7);
	m_profile->GetComponent<Transform>()->SetPosition({ 550, 985 });

	Img = m_babyprofile->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("baby_profile1.png"), { 80, 80 });
	Img->SetOrderInLayer(7);
	m_babyprofile->GetComponent<Transform>()->SetPosition({ 550, 875 });

	Img = m_hungryImage->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("hungry1.png"), { 62, 62 });
	Img->SetOrderInLayer(7);
	m_hungryImage->GetComponent<Transform>()->SetPosition({ 665, 880 });

	m_hp1->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Heart.png"), { 72, 65 });
	m_hp1->GetComponent<Transform>()->SetPosition({ 685, 980 });
	m_hp2->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Heart.png"), { 72, 65 });
	m_hp2->GetComponent<Transform>()->SetPosition({ 770, 980 });
	m_hp3->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Heart.png"), { 72, 65 });
	m_hp3->GetComponent<Transform>()->SetPosition({ 855, 980 });

	m_hungryBG->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("gauge_frame.png"), { 300, 90 });
	m_hungryBG->GetComponent<Transform>()->SetPosition({ 770, 880 });

	m_hungryGauge->AddComponent<Image>();
	m_hungryGauge->AddComponent<Slide_Bar>();
	m_hungryGauge->AddComponent<HungryGauge>();
	m_hungryGauge->GetComponent<Transform>()->SetPosition({ 805, 879 });

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
	ui_score->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("Sign_Panel.png"), { 270, 108 });
	ui_score->GetComponent<Transform>()->SetPosition(Vector2{ 1755, 100 });

#pragma endregion

#pragma region OutRange

	m_outRangeUp = Instantiate("outRangeUp");
	m_outRangeDown = Instantiate("outRangeDown");
	m_outRangeRight = Instantiate("outRangeRight");
	m_outRangeLeft = Instantiate("outRangeLeft");

	m_outRangeUp->SetTag("OutRange");
	m_outRangeDown->SetTag("OutRange");
	m_outRangeRight->SetTag("OutRange");
	m_outRangeLeft->SetTag("OutRange");

	BoxCollider* box = m_outRangeUp->AddComponent<BoxCollider>();
	box->SetSize({ 7680 , 100 });
	box = m_outRangeDown->AddComponent<BoxCollider>();
	box->SetSize({ 7680 , 100 });
	box = m_outRangeRight->AddComponent<BoxCollider>();
	box->SetSize({ 100 , 4320 });
	box = m_outRangeLeft->AddComponent<BoxCollider>();
	box->SetSize({ 100 , 4320 });

	m_outRangeUp->GetComponent<Transform>()->SetPosition({ 0, 300.000 });
	m_outRangeDown->GetComponent<Transform>()->SetPosition({ 0, -300.000 });
	m_outRangeRight->GetComponent<Transform>()->SetPosition({ 3580.000, 0 });
	m_outRangeLeft->GetComponent<Transform>()->SetPosition({ -3580.000, 0 });

#pragma endregion

	GameManager::Instance().Init(); //player??inventory ?°ê²°.
#pragma region	ESC

	m_Esc = Instantiate("ESC");
	m_EscBG = Instantiate("EscBG");
	m_TitleBtn = Instantiate("TitleBtn");
	m_SettingBtn = Instantiate("settingBtn");
	
	m_Esc->AddComponent<EscBtn>();

	Img = m_EscBG->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Setting.png"), { 500, 500 });
	Img->SetOrderInLayer(5);

	Img = m_TitleBtn->AddComponent<Image>();
	auto btn = m_TitleBtn->AddComponent<Button>();
	Img->SetOrderInLayer(6);
	m_TitleBtn->AddComponent<TitleBtn>();

	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);

	Img = m_SettingBtn->AddComponent<Image>();
	btn = m_SettingBtn->AddComponent<Button>();
	Img->SetOrderInLayer(6);
	m_SettingBtn->AddComponent<SettingButton>();

	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);

	m_EscBG->GetComponent<Transform>()->SetPosition({ 960, 540 });
	m_TitleBtn->GetComponent<Transform>()->SetPosition({ 960, 440 });
	m_SettingBtn->GetComponent<Transform>()->SetPosition({ 960, 630 });

	m_EscBG->SetActive(false);
	m_TitleBtn->SetActive(false);
	m_SettingBtn->SetActive(false);


	//Sound Setting Wnd
	m_settingWnd = Instantiate("settingWnd");
	m_settingText = Instantiate("settingText");
	m_bgmText = Instantiate("bgmText");
	m_bgmSlider = Instantiate("bgmSlider");
	m_sfxText = Instantiate("sfxText");
	m_sfxSlider = Instantiate("sfxSlider");
	m_uiText = Instantiate("uiText");
	m_uiSlider = Instantiate("uiSlider");
	m_cancleBtn = Instantiate("cancleBtn");
	m_checkBtn = Instantiate("checkBtn");

	Img = m_settingWnd->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Setting.png"), { 900, 700 });
	Img->SetOrderInLayer(7);

	txt = m_settingText->AddComponent<Text>();
	txt->SetText(L"Sound", { 200, 100 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(50);
	txt->SetOrderLayer(7);

	//bgm setting
	txt = m_bgmText->AddComponent<Text>();
	txt->SetText(L"BGM Volume", { 200, 70 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(30);
	txt->SetOrderLayer(7);

	Img = m_bgmSlider->AddComponent<Image>();
	auto sb = m_bgmSlider->AddComponent<Slide_Bar>();
	btn = m_bgmSlider->AddComponent<Button>();
	m_bgmSlider->GetComponent<Transform>()->SetPosition({ 830, 340 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 500, 20 });
	Img->SetOrderInLayer(7);
	btn->SetSize({ 500,20 });
	sb->RegisterButton(btn);

	//sfx setting
	txt = m_sfxText->AddComponent<Text>();
	txt->SetText(L"SFX Volume", { 200, 70 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(30);
	txt->SetOrderLayer(7);

	Img = m_sfxSlider->AddComponent<Image>();
	sb = m_sfxSlider->AddComponent<Slide_Bar>();
	btn = m_sfxSlider->AddComponent<Button>();
	m_sfxSlider->GetComponent<Transform>()->SetPosition({ 830, 440 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 500, 20 });
	Img->SetOrderInLayer(7);
	btn->SetSize({ 500,20 });
	sb->RegisterButton(btn);

	//ui setting
	txt = m_uiText->AddComponent<Text>();
	txt->SetText(L"UI Volume", { 200, 70 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(30);
	txt->SetOrderLayer(7);

	Img = m_uiSlider->AddComponent<Image>();
	sb = m_uiSlider->AddComponent<Slide_Bar>();
	btn = m_uiSlider->AddComponent<Button>();
	m_uiSlider->GetComponent<Transform>()->SetPosition({ 830, 540 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 500, 20 });
	Img->SetOrderInLayer(7);
	btn->SetSize({ 500,20 });
	sb->RegisterButton(btn);

	//button setting
	Img = m_cancleBtn->AddComponent<Image>();
	btn = m_cancleBtn->AddComponent<Button>();
	m_cancleBtn->AddComponent<QuitSettingBtn>();
	Img->SetOrderInLayer(7);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);
	btn->SetSize({ 160, 100 });

	Img = m_checkBtn->AddComponent<Image>();
	btn = m_checkBtn->AddComponent<Button>();
	m_checkBtn->AddComponent<AcceptSettingBtn>();
	Img->SetOrderInLayer(7);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);
	btn->SetSize({ 160, 100 });

	m_settingWnd->GetComponent<Transform>()->SetPosition({ 960, 435 });
	m_settingText->GetComponent<Transform>()->SetPosition({ 960, 170 });
	m_bgmText->GetComponent<Transform>()->SetPosition({ 660, 300 });
	m_sfxText->GetComponent<Transform>()->SetPosition({ 660, 400 });
	m_uiText->GetComponent<Transform>()->SetPosition({ 660, 500 });
	m_cancleBtn->GetComponent<Transform>()->SetPosition({ 860, 700 });
	m_checkBtn->GetComponent<Transform>()->SetPosition({ 1060, 700 });

	m_settingWnd->SetActive(false);
	m_settingText->SetActive(false);
	m_bgmText->SetActive(false);
	m_bgmSlider->SetActive(false);
	m_sfxText->SetActive(false);
	m_sfxSlider->SetActive(false);
	m_uiText->SetActive(false);
	m_uiSlider->SetActive(false);
	m_cancleBtn->SetActive(false);
	m_checkBtn->SetActive(false);
	//Sound Setting End

#pragma endregion

	m_skipBtn = Instantiate("skipBtn");
	Img = m_skipBtn->AddComponent<Image>();
	btn = m_skipBtn->AddComponent<Button>();
	m_skipBtn->AddComponent<SkipButton>();

	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn2_Start.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn2_Start_Select.png"), ButtonEvent::Highlight);

	m_skipBtn->GetComponent<Transform>()->SetPosition({ 1760, 220 });

	GameManager::Instance().Init(); //player?ž‘ inventory ?—°ê²?.
	SoundManager::Instance().BGM_Shot("2.mp3");

	Scene::Awake();
}

void TutorialScene::Start()
{
	if (!IsActive())
		return;

    main_Cam = GetCamera();
    main_Cam->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(player);


	Scene::Start();
}
