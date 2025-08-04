#pragma once
class PlayerAnimator : public MonoBehaviour
{
public:
	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;
	/*void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;*/

	void ActionAnime();
	void UpdateVisible();

private:
	Player* m_Player = nullptr;
	Animator* m_animator = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
};

