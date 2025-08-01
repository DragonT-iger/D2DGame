#include "pch.h"
#include "HSTestScene.h"
#include "PlayerController.h"
#include "UITest.h"
#include "Crop.h"
#include "InventorySlot.h"
#include "Inventory.h"
#include "PlayerController_Sample.h"
#include "CinemachineCamera.h"
#include "SpawnManager.h"

void HSTestScene::Awake()
{
	if (!IsActive())
		return;

	/* ********����********
		Awake���� Scene::Awake() ���� ���ӿ�����Ʈ���ٰ� ������Ʈ�� �ټ� ���� ��������
	*/
	m_SpawnManager = Instantiate("SpawnManager");

	m_SpawnManager->AddComponent<SpawnManager>();

	m_inventory = Instantiate("Inventory");
	m_inventory->AddComponent<Image>()->SetBitmap(ResourceManager::Instance().LoadTexture("inventoryBG.png"), {1200, 300});
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

	m_slot2 = Instantiate("Slot2");
	m_slot2->AddComponent<Image>();
	m_slot2->AddComponent<Slot>();
	m_slot2->GetComponent<Transform>()->SetPosition({ 950, 930 });
	m_slot2->GetComponent<Transform>()->SetParent(m_slot2BG->GetComponent<Transform>());

	m_slot3 = Instantiate("Slot3");
	m_slot3->AddComponent<Image>();
	m_slot3->AddComponent<Slot>();
	m_slot3->GetComponent<Transform>()->SetPosition({ 1350, 930 });
	m_slot3->GetComponent<Transform>()->SetParent(m_slot3BG->GetComponent<Transform>());

	SoundManager::Instance().Init();
	SoundManager::Instance().BGM_Shot("sample_ten.wav");

	m_background = Instantiate("background");

	m_spriteRenderer = m_background->AddComponent<SpriteRenderer>();

	m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("Test_back_02.png"));

	m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });



	// �ϴ��� Awake���� ���� �ʱ�ȭ�ϴ� �ɷ�
	// ���� ���ӿ�����Ʈ �ʱ�ȭ�� �����	(�ν����� �����ϼ�)


	Scene::Awake();
}


void HSTestScene::Start()
{

	// ��Ȯ�� ���ؾ��� start ���� ���� �����ϸ� Awake���� ó���ϼ���

	if (!IsActive())
		return;

	// ī�޶�� awake���� �ʱ�ȭ�ż� �׳� ���⼭ ����

	Camera* camera = GetCamera();

	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_background);

	Scene::Start();
}
