#include "pch.h"
#include "StartButton.h";
#include "TestTitleScene.h"

void TitleScene::Awake()
{
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Light.ttf"), L"Maplestory");
	D2DRenderer::Instance().RegisterFont(ResourceManager::Instance().GetFontPath("Maplestory_Bold.ttf"), L"Maplestory");

	m_startButton = Instantiate("startBtn");

	auto Img = m_startButton->AddComponent<Image>();
	auto button = m_startButton->AddComponent<Button>();
	m_startButton->AddComponent<StartButton>();

	button->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_basic100.png"), ButtonEvent::Idle);
	button->AddEventSprite(ResourceManager::Instance().LoadTexture("button1_mouse_click.png"), ButtonEvent::Highlight);

	m_startButton->GetComponent<Transform>()->SetPosition({ 960.f, 540.f });

	m_Title = Instantiate("title");
	auto text = m_Title->AddComponent<Text>();

	text->SetText(L"����������", { 400, 100 }, L"Maplestory", D2D1::ColorF::Black);
	text->SetFontSize(50);

	m_Title->GetComponent<Transform>()->SetPosition({ 960, 440 });

	// �ϴ��� Awake���� ���� �ʱ�ȭ�ϴ� �ɷ�
	// ���� ���ӿ�����Ʈ �ʱ�ȭ�� �����	(�ν����� �����ϼ�)
	Scene::Awake();
}

void TitleScene::Start()
{
	Scene::Start();
}
