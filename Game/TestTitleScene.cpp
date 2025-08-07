#include "pch.h"
#include "StartButton.h";
#include "SettingButton.h"
#include "AcceptSetting.h"
#include "QuitSetting.h"
#include "TestTitleScene.h"

void TitleScene::Awake()
{
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Light.ttf"), L"Maplestory");
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Bold.ttf"), L"Maplestory");

#pragma region Button_Instantiate
	m_startButton = Instantiate("startBtn");
	m_settingButton = Instantiate("settingBtn");
	m_quitButton = Instantiate("quitBtn");
	
	auto Img = m_startButton->AddComponent<Image>();
	auto button = m_startButton->AddComponent<Button>();
	m_startButton->AddComponent<StartButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);

	Img = m_settingButton->AddComponent<Image>();
	button = m_settingButton->AddComponent<Button>();
	m_settingButton->AddComponent<SettingButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);

	m_startButton->GetComponent<Transform>()->SetPosition({ 960.f, 540.f });
	m_settingButton->GetComponent<Transform>()->SetPosition({ 960.f, 640.f });

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
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("CurSlot.png"), { 900, 700 });
	Img->SetOrderInLayer(3);

	auto txt = m_settingText->AddComponent<Text>();
	txt->SetText(L"설정", { 200, 100 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(50);
	txt->SetOrderLayer(4);

	//bgm setting
	txt = m_bgmText->AddComponent<Text>();
	txt->SetText(L"BGM Volume", { 200, 70 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(30);
	txt->SetOrderLayer(4);

	Img = m_bgmSlider->AddComponent<Image>();
	auto sb = m_bgmSlider->AddComponent<Slide_Bar>();
	auto btn = m_bgmSlider->AddComponent<Button>();
	m_bgmSlider->GetComponent<Transform>()->SetPosition({ 830, 340 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 500, 20 });
	Img->SetOrderInLayer(4);
	btn->SetSize({ 500,20 });
	sb->RegisterButton(btn);

	//sfx setting
	txt = m_sfxText->AddComponent<Text>();
	txt->SetText(L"SFX Volume", { 200, 70 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(30);
	txt->SetOrderLayer(4);

	Img = m_sfxSlider->AddComponent<Image>();
	sb = m_sfxSlider->AddComponent<Slide_Bar>();
	btn = m_sfxSlider->AddComponent<Button>();
	m_sfxSlider->GetComponent<Transform>()->SetPosition({ 830, 440 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 500, 20 });
	Img->SetOrderInLayer(4);
	btn->SetSize({ 500,20 });
	sb->RegisterButton(btn);

	//ui setting
	txt = m_uiText->AddComponent<Text>();
	txt->SetText(L"UI Volume", { 200, 70 }, L"Maplestory", D2D1::ColorF::Black);
	txt->SetFontSize(30);
	txt->SetOrderLayer(4);

	Img = m_uiSlider->AddComponent<Image>();
	sb = m_uiSlider->AddComponent<Slide_Bar>();
	btn = m_uiSlider->AddComponent<Button>();
	m_uiSlider->GetComponent<Transform>()->SetPosition({ 830, 540 });
	Img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 500, 20 });
	Img->SetOrderInLayer(4);
	btn->SetSize({ 500,20 });
	sb->RegisterButton(btn);

	//button setting
	Img = m_cancleBtn->AddComponent<Image>();
	btn = m_cancleBtn->AddComponent<Button>();
	m_cancleBtn->AddComponent<QuitSettingBtn>();
	Img->SetOrderInLayer(4);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	btn->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);
	btn->SetSize({ 160, 100 });

	Img = m_checkBtn->AddComponent<Image>();
	btn = m_checkBtn->AddComponent<Button>();
	m_checkBtn->AddComponent<AcceptSettingBtn>();
	Img->SetOrderInLayer(4);
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

#pragma endregion

	SoundManager::Instance().SetVolume_BGM(1.f);
	SoundManager::Instance().SetVolume_SFX(1.f);
	SoundManager::Instance().SetVolume_UI(1.f);

	//SoundManager::Instance().BGM_Shot("sample_ten.wav");

	m_Title = Instantiate("title");
	auto text = m_Title->AddComponent<Text>();

	text->SetText(L"몰래몰래팜", { 400, 100 }, L"Maplestory", D2D1::ColorF::Black);
	text->SetFontSize(50);

	m_Title->GetComponent<Transform>()->SetPosition({ 960, 440 });

	// 일단은 Awake에서 씬을 초기화하는 걸로
	// 씬은 게임오브젝트 초기화만 담당함	(인스펙터 생각하셈)
	Scene::Awake();
}

void TitleScene::Start()
{
	Scene::Start();
}
