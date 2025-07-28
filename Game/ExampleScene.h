#pragma once
class ExampleScene : public Scene
{
	void Awake() override;
	void Start() override;



	Transform* m_playerTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
	Camera* m_camera = nullptr;
	GameObject* m_player = nullptr;
	GameObject* m_player2 = nullptr;
};

