#pragma once

class TutorialScene : public Scene
{
	void Awake() override;
	void Start() override;


	Camera* main_Cam = nullptr;

	GameObject* player = nullptr;
	Transform* player_T = nullptr;
	SpriteRenderer* player_S = nullptr;
};

