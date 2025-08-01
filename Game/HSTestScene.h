#pragma once

class HSTestScene : public Scene
{
	void Awake() override;
	void Start() override;



	Transform* m_playerTransform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
	Camera* m_camera = nullptr;

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
