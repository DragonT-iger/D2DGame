#include "pch.h"
#include "MainScene.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"

void MainScene::Awake()
{
	if (!IsActive())
		return;

	player = Instantiate("Player");
	player_S = player->AddComponent<SpriteRenderer>();
	player->AddComponent<PlayerController>();
	player->AddComponent<BoxCollider>();
	player->AddComponent<Animator>();
	player->AddComponent<CircleCollider>();

	PlayerController* pc = player->AddComponent<PlayerController>();

	pc->m_Spd_X = 1500.0f;
	pc->m_Spd_Y = 1500.0f;

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