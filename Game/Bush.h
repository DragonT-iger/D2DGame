#pragma once

class Bush : public MonoBehaviour
{
public:
	void Awake()                         override;
	void Start()                         override;
	//void Update(float deltaTime)         override;
	void OnTriggerEnter(Collider* other) override;
	//void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;

private:
	Transform* m_transform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
	Animator* m_animator = nullptr;
	BoxCollider* m_boxCol = nullptr;
};

