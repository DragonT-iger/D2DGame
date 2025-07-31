#pragma once
class PlayerController : public MonoBehaviour
{
public:

	enum class Action
	{
		Idle,
		Walk,
		Hit,
		Steal,
		Alive,
		Dead
	};

	enum class Visibilty
	{
		Hide,
		Visible
	};

	//enum class State
	//{
	//	Alive,
	//	Dead
	//};

	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	//void OnTriggerEnter(Collider* other) override;
	//void OnTriggerStay(Collider* other)  override;
	//void OnTriggerExit(Collider* other)  override;

	float m_Spd;
	bool m_canMove = true;
private:

	Action state = Action::Idle;

	std::string str_currentState;
	Animator* m_animator = nullptr;
	Transform* m_transform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
};

