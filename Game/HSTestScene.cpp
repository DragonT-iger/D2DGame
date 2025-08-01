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

	/* ********주의********
		Awake에서 Scene::Awake() 전에 게임오브젝트에다가 컴포넌트만 다셈 딴건 하지마샘
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



	// 일단은 Awake에서 씬을 초기화하는 걸로
	// 씬은 게임오브젝트 초기화만 담당함	(인스펙터 생각하셈)


	Scene::Awake();
}


void HSTestScene::Start()
{

	// 정확한 이해없이 start 쓰지 마셈 가능하면 Awake에서 처리하세요

	if (!IsActive())
		return;

	// 카메라는 awake에서 초기화돼서 그냥 여기서 적음

	Camera* camera = GetCamera();

	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_background);

	Scene::Start();
}
