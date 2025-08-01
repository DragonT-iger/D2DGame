#pragma once
class Player : public MonoBehaviour
{
public:

	enum class State
	{
		Alive,
		Dead
	};

	enum class Action
	{
		Idle,
		Walk,
		Hit,
		Steal,
	};

	enum class Visibilty
	{
		Hide,
		Visible
	};


	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;

	State& GetState() { return state; }
	Action& GetAction() { return action; }
	Visibilty& GetVisibilty() { return visibilty; }
		
private:
	int     hp			= 3;
	float   spd			= 500.0f;
	//float starv_level = 500.0f;
	int		ivc_T		= 15;

	static int invincible_Count;

	State		state		= State::Alive;
	Action		action		= Action::Idle;
	Visibilty	visibilty	= Visibilty::Visible;

	Animator* m_animator = nullptr;
	Transform* m_transform = nullptr;
	SpriteRenderer* m_spriteRenderer = nullptr;
};

