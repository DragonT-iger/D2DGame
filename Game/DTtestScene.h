#pragma once
class DTtestScene : public Scene
{
	void Awake() override;
	void Start() override;

	Camera* main_Cam = nullptr;

	GameObject* player = nullptr;
	Transform* player_T = nullptr;
	SpriteRenderer* player_S = nullptr;

	GameObject* crop = nullptr;
	GameObject* message = nullptr;
	GameObject* bush = nullptr;





	//Farmer

	GameObject* m_farmerManager = nullptr;


	GameObject* m_inventory = nullptr;
	GameObject* m_slot1BG = nullptr;
	GameObject* m_slot2BG = nullptr;
	GameObject* m_slot3BG = nullptr;
	GameObject* m_slot1 = nullptr;
	GameObject* m_slot2 = nullptr;
	GameObject* m_slot3 = nullptr;
	GameObject* m_background = nullptr;
	GameObject* m_SpawnManager = nullptr;
};

