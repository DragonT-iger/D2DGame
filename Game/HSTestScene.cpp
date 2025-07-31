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

	/* ********����********
		Awake���� Scene::Awake() ���� ���ӿ�����Ʈ���ٰ� ������Ʈ�� �ټ� ���� ��������
	*/
	m_SpawnManager = Instantiate("SpawnManager");

	m_SpawnManager->AddComponent<SpawnManager>();

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

	camera->GetOwner()->GetComponent<CinemachineCamera>()->SetPlayer(m_player2);

	Scene::Start();
}
