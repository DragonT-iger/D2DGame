#pragma once
class PlayerController : public MonoBehaviour
{
public:
	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	//void OnTriggerEnter(Collider* other) override;
	//void OnTriggerStay(Collider* other)  override;
	//void OnTriggerExit(Collider* other)  override;

private:
	float m_Spd_X = 10.0f;
	float m_Spd_Y = 10.0f;

	Animator* m_animator = nullptr;
	Transform* m_transform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
};

