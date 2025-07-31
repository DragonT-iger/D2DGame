#include "pch.h"
#include "HSTestScene.h"
#include "PlayerController.h"
#include "UITest.h"
#include "Crop.h"
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

	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_player2);

	Scene::Start();
}
