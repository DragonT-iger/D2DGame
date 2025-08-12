#pragma once
class PlayerShadow : public MonoBehaviour
{
	public:
		void Awake()                         override;
		void Start()                         override;
		void Update(float deltaTime)         override;
		//void OnTriggerEnter(Collider* other) override;
		//void OnTriggerStay(Collider* other)  override;
		//void OnTriggerExit(Collider* other)  override;

		GameObject* m_playerObj = nullptr;
		SpriteRenderer* m_spriteRenderer = nullptr;
};

