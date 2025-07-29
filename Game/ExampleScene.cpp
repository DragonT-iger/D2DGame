#include "pch.h"
#include "ExampleScene.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"

void ExampleScene::Awake()
{
	if(!IsActive())
		return;

	/* ********����********
		Awake���� Scene::Awake() ���� ���ӿ�����Ʈ���ٰ� ������Ʈ�� �ټ� ���� ��������
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

	m_background = Instantiate(L"background");

	m_spriteRenderer = m_background->AddComponent<SpriteRenderer>();

	m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("Test_back_02.png"));

	m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

	m_player = Instantiate(L"Player");

	m_player->SetTag(L"Player");

	m_spriteRenderer = m_player->AddComponent<SpriteRenderer>();
	m_player->AddComponent<Animator>();
	// �Ҵ� �ȵż� assert �ɸ�
	
	m_player->AddComponent<PlayerController>();

	m_player->GetComponent<Transform>()->SetPosition({ 100.f, 100.f });

	m_player->AddComponent<BoxCollider>();

	b->AddPressEvent([this]() {m_player->GetComponent<Transform>()->Translate({ 20.f, 20.f }); });
	b->AddPressEvent([]() { std::cout << "��ư ������2" << std::endl; });

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

	
	// �ϴ��� Awake���� ���� �ʱ�ȭ�ϴ� �ɷ�
	// ���� ���ӿ�����Ʈ �ʱ�ȭ�� �����	(�ν����� �����ϼ�)


	Scene::Awake();
}


void ExampleScene::Start()
{

	// ��Ȯ�� ���ؾ��� start ���� ���� �����ϸ� Awake���� ó���ϼ���
	
	if (!IsActive())
		return;

	// ī�޶�� awake���� �ʱ�ȭ�ż� �׳� ���⼭ ����

	Camera* camera = GetCamera();
	
	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_player2);











	Scene::Start();
}
