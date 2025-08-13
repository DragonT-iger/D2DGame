#include "pch.h"
#include "StartButton.h";
#include "SettingButton.h"
#include "AcceptSetting.h"
#include "QuitSetting.h"
#include "CreditBtn.h"
#include "QuitBtn.h"
#include "TitleScene.h"

void TitleScene::Awake()
{
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Light.ttf"), L"Maplestory");
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Bold.ttf"), L"Maplestory");
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("HakgyoansimTuhoR.ttf"), L"Hakgyoansim Tuho");

#pragma region Button_Instantiate
	m_startButton = Instantiate("startBtn");
	m_settingButton = Instantiate("settingBtn");
	m_creditButton = Instantiate("creditBtn");
	m_quitButton = Instantiate("quitBtn");
	m_buttonBG = Instantiate("buttonBG");

	auto Img = m_buttonBG->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("TitleBtn1_farm.png"), { 1920, 1080 });
	Img->SetOrderInLayer(-500);
	
	Img = m_startButton->AddComponent<Image>();
	auto button = m_startButton->AddComponent<Button>();
	m_startButton->AddComponent<StartButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn2_Start.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn2_Start_Select.png"), ButtonEvent::Highlight);

	Img = m_settingButton->AddComponent<Image>();
	button = m_settingButton->AddComponent<Button>();
	m_settingButton->AddComponent<SettingButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn3_Setting.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn3_Setting_Select.png"), ButtonEvent::Highlight);

	Img = m_creditButton->AddComponent<Image>();
	button = m_creditButton->AddComponent<Button>();
	m_creditButton->AddComponent<CreditButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn4_Credit.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn4_Credit_Select.png"), ButtonEvent::Highlight);

	Img = m_quitButton->AddComponent<Image>();
	button = m_quitButton->AddComponent<Button>();
	m_quitButton->AddComponent<QuitButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn5_Exit.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("TitleBtn5_Exit_Select.png"), ButtonEvent::Highlight);

	m_startButton->GetComponent<Transform>()->SetPosition({ 1700.f, 520.f });
	m_settingButton->GetComponent<Transform>()->SetPosition({ 1700.f, 680.f });
	m_creditButton->GetComponent<Transform>()->SetPosition({ 1675.f, 820.f });
	m_quitButton->GetComponent<Transform>()->SetPosition({ 1700.f, 960.f });
	m_buttonBG->GetComponent<Transform>()->SetPosition({ 960, 540 });

#pragma endregion

#pragma region SettingWindow_Instantiate

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
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Setting_Panel_900x700.png"), { 900, 700 });
	Img->SetOrderInLayer(3);

	Img = m_bgmSlider->AddComponent<Image>();
	auto sb = m_bgmSlider->AddComponent<Slide_Bar>();
	auto btn = m_bgmSlider->AddComponent<Button>();
	m_bgmSlider->GetComponent<Transform>()->SetPosition({ 1021, 387 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("guage_fill_67x67.png"), { 382, 53 });
	Img->SetOrderInLayer(4);
	btn->SetSize({ 382, 70 });
	sb->RegisterButton(btn);

	//sfx setting
	Img = m_sfxSlider->AddComponent<Image>();
	sb = m_sfxSlider->AddComponent<Slide_Bar>();
	btn = m_sfxSlider->AddComponent<Button>();
	m_sfxSlider->GetComponent<Transform>()->SetPosition({ 1021, 519 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("guage_fill_67x67.png"), { 382, 53 });
	Img->SetOrderInLayer(4);
	btn->SetSize({ 382, 70 });
	sb->RegisterButton(btn);

	//ui setting
	Img = m_uiSlider->AddComponent<Image>();
	sb = m_uiSlider->AddComponent<Slide_Bar>();
	btn = m_uiSlider->AddComponent<Button>();
	m_uiSlider->GetComponent<Transform>()->SetPosition({ 1021, 645 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("guage_fill_67x67.png"), { 382, 53 });
	Img->SetOrderInLayer(4);
	btn->SetSize({ 382, 70 });
	sb->RegisterButton(btn);

	//button setting
	Img = m_cancleBtn->AddComponent<Image>();
	btn = m_cancleBtn->AddComponent<Button>();
	m_cancleBtn->AddComponent<QuitSettingBtn>();
	Img->SetOrderInLayer(4);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("Setting_Btn1_Title.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("Setting_Btn1_Title_Selected.png"), ButtonEvent::Highlight);
	btn->SetSize({ 200, 80 });

	Img = m_checkBtn->AddComponent<Image>();
	btn = m_checkBtn->AddComponent<Button>();
	m_checkBtn->AddComponent<AcceptSettingBtn>();
	Img->SetOrderInLayer(4);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("Setting_Btn2_Title.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("Setting_Btn2_Title_Selected.png"), ButtonEvent::Highlight);
	btn->SetSize({ 200, 80 });

	m_settingWnd->GetComponent<Transform>()->SetPosition({ 960, 540 });
	m_settingText->GetComponent<Transform>()->SetPosition({ 960, 170 });
	m_bgmText->GetComponent<Transform>()->SetPosition({ 660, 300 });
	m_sfxText->GetComponent<Transform>()->SetPosition({ 660, 400 });
	m_uiText->GetComponent<Transform>()->SetPosition({ 660, 500 });
	m_cancleBtn->GetComponent<Transform>()->SetPosition({ 820, 790 });
	m_checkBtn->GetComponent<Transform>()->SetPosition({ 1100, 790 });

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

#pragma endregion

	m_credit = Instantiate("credit");
	Img = m_credit->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Credit.png"), { 1920, 1080 });
	Img->SetOrderInLayer(20);

	SoundManager::Instance().SetVolume_BGM(1.f);
	SoundManager::Instance().SetVolume_SFX(1.f);
	SoundManager::Instance().SetVolume_UI(1.f);

	SoundManager::Instance().BGM_Shot("1.mp3");

	m_Title = Instantiate("title");
	auto sp = m_Title->AddComponent<SpriteRenderer>();
	auto anim = m_Title->AddComponent<Animator>();
	auto clip = ResourceManager::Instance().LoadAnimationClip("illust_animation_final_2.json", "title");
	anim->AddClip("title", clip);
	sp->SetOrderInLayer(-10000);

	m_Title->GetComponent<Transform>()->SetPosition({ 0, 0 });

	m_TitleLogo = Instantiate("titleLogo");
	Img = m_TitleLogo->AddComponent<Image>();
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("Title_Logo.png"), { 713, 451 });

	m_TitleLogo->GetComponent<Transform>()->SetPosition({ 960, 230 });

	// 일단은 Awake에서 씬을 초기화하는 걸로
	// 씬은 게임오브젝트 초기화만 담당함	(인스펙터 생각하셈)
	Scene::Awake();
}

void TitleScene::Start()
{
	Scene::Start();
}
