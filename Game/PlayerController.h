#pragma once

class Player;
class SpawnManager;
class Inventory;
enum Crops;


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

	float m_throwDelay = 0.3f;
	float m_delay = 0.0f; // 0¿” ¿Ã∞«


	float m_throwTime = 0.1f;
	float m_throwelapsedTime = 0.f;

	float m_speedBoost = 0.0f;
	float m_boostTimer = 0.0f;

	void SpawnThrownCrop(Crops type);
	void ApplyThrowBoost(Crops type);

	//float* p_Spd = nullptr;
};