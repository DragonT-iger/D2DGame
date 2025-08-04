#pragma once
class MainScene : public Scene
{
	void Awake() override;
	void Start() override;
	void Update(float deltaTime);

	Camera*					main_Cam	= nullptr;

	GameObject*				player		= nullptr;
	Transform*				player_T	= nullptr;
	SpriteRenderer*			player_S	= nullptr;

	GameObject*				crop		= nullptr;
	GameObject*				message		= nullptr;
	GameObject*				bush = nullptr;
};

