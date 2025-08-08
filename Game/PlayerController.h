#pragma once

class Player;
class SpawnManager;
class Inventory;

class PlayerController : public MonoBehaviour
{
public:

	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;

	void SetSpawnManager(SpawnManager* spm_ptr) { m_SpawnManager = spm_ptr; }

private:


	Player* m_Player = nullptr;
	Transform* m_transform = nullptr;
	Animator* m_animator = nullptr;

	SpawnManager* m_SpawnManager = nullptr;
	Inventory* m_inven = nullptr;

	Vector2 curDir;

	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

	float m_throwTime = 0.2f;
	float m_throwelapsedTime = 0.0f;

	//float* p_Spd = nullptr;
};