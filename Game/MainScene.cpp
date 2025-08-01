#include "pch.h"
#include "MainScene.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"
#include "Crop.h"

void MainScene::Awake()
{
	if (!IsActive())
		return;

//begin player-----
	player = Instantiate("Player");
	player->AddComponent<SpriteRenderer>();
	player->AddComponent<PlayerController>();
	player->AddComponent<BoxCollider>();
	player->AddComponent<Animator>();
//end player-----


//begin crop-----
	crop = Instantiate("Crop");
	crop->SetTag("crop");

	crop->AddComponent<SpriteRenderer>();
	crop->AddComponent<BoxCollider>();
	crop->AddComponent<Animator>();
	auto crop_scripts	= crop->AddComponent<Crop>();

	crop->GetComponent<Transform>()->SetPosition(Vector2{0,0});
	crop->GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> cropbit = {
		ResourceManager::Instance().LoadTexture("potatoL.png"),
		ResourceManager::Instance().LoadTexture("potatoL.png"),
		ResourceManager::Instance().LoadTexture("potatoL.png")
	};

	crop_scripts->SetCropData((FarmRank)0, (Crops)1, cropbit);

//end crop------

//begin message-----

	message = Instantiate("steal_message");
	
	auto message_render = message->AddComponent<SpriteRenderer>();
	message->GetComponent<Transform>()->SetParent(crop->GetComponent<Transform>());

	message->GetComponent<Transform>()->SetPosition(Vector2{ 0,250 });
	message->GetComponent<Transform>()->SetScale({ 0.5f, 0.5f });

	message_render->SetBitmap(ResourceManager::Instance().LoadTexture("steal_message.png"));

	message->SetActive(false);
	

//end message-----


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

void MainScene::Update(float deltaTime)
{
	message->GetComponent<Transform>()->SetPosition(Vector2{ 0,250 });
}