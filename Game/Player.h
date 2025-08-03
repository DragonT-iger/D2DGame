#pragma once

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

class Player : public MonoBehaviour
{
public:

	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;

	State& GetState_ref() { return state; }
	Action& GetAction_ref() { return action; }
	Visibilty& GetVisibilty_ref() { return visibilty; }

	float& GetSpd_ref() { return m_spd; }

private:
	int     m_hp			= 3;
	float   m_spd			= 500.0f;
	//float m_starv_level   = 500.0f;
	int		m_ivc_T		    = 15;						//fps ±‚¡ÿ

	static int invincible_Count;

	State		state		= State::Alive;
	Action		action		= Action::Idle;
	Visibilty	visibilty	= Visibilty::Visible;
};

