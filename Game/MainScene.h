#pragma once
class MainScene : public Scene
{
	void Awake() override;
	void Start() override;

	Camera*					main_Cam	= nullptr;

	GameObject*				player		= nullptr;
	Transform*				player_T	= nullptr;
	SpriteRenderer*			player_S	= nullptr;

	GameObject*				crop		= nullptr;
	GameObject*				message		= nullptr;
	GameObject*				bush = nullptr;

	GameObject*				SubMissionArea1 = nullptr;
	GameObject*				SubMissionArea2 = nullptr;

	
	GameObject*				ui_score = nullptr;


	//Farmer

	GameObject* m_farmerManager = nullptr;

	GameObject* m_farmerHouse = nullptr;

	GameObject* m_Timer;

	GameObject* m_inventory = nullptr;
		GameObject* m_slot1BG = nullptr;
		GameObject* m_slot2BG = nullptr;
		GameObject* m_slot3BG = nullptr;
		GameObject* m_slot1 = nullptr;
		GameObject* m_slot2 = nullptr;
		GameObject* m_slot3 = nullptr;
		GameObject* m_slot1Text = nullptr;
		GameObject* m_slot2Text = nullptr;
		GameObject* m_slot3Text = nullptr;

		GameObject* m_profile = nullptr;
		GameObject* m_profileBG = nullptr;
		GameObject* m_babyprofile = nullptr;
		GameObject* m_babyprofileBG = nullptr;

		GameObject* m_hungryBG = nullptr;
		GameObject* m_hungryGauge = nullptr;
		GameObject* m_hungryImage = nullptr;

		GameObject* m_hp1 = nullptr;
		GameObject* m_hp2 = nullptr;
		GameObject* m_hp3 = nullptr;

	GameObject* m_background = nullptr;

	GameObject* m_SpawnManager = nullptr;
};

