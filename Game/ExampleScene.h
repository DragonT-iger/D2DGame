#pragma once
class ExampleScene : public Scene
{
	void Awake() override;
	void Start() override;


	GameObject* m_farmer = nullptr;

	Transform* m_playerTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
	Camera* m_camera = nullptr;
	GameObject* m_player = nullptr;
	GameObject* m_player2 = nullptr;
	GameObject*			m_button = nullptr;
	GameObject*			m_slidebar = nullptr;
	GameObject*			m_background = nullptr;
	GameObject*			m_SpawnManager = nullptr;
};

