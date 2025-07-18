#pragma once
class MainScene : public Scene
{
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;



	Transform* m_playerTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
	GameObject* m_player = nullptr;
};

