#pragma once

enum class State
{
	Alive,
	Dead,
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
	Visible,
};

class Player : public MonoBehaviour
{
public:
	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;

	//void SetState(State ste);
	//void SetAction(Action act);
	//void SetVisible(Visibilty vib);
	//
	//State GetState() { return state; }
	//Action GetAction() { return action; }
	//Visibilty GetVisible() { return visibilty; }

	friend class PlayerController;
	friend class PlayerAnimator;

private:
	int     m_hp			= 3;
	float   m_spd			= 500.0f;
	//float m_starv_level   = 500.0f;
	int		m_ivc_T		    = 15;						//fps ±‚¡ÿ

	static int invincible_Count;

	State		state		= State::Alive;
	Action		action		= Action::Idle;
	Visibilty	visibilty	= Visibilty::Visible;

	BoxCollider* m_boxCol = nullptr;
};

