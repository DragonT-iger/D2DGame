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

class Inventory;
class Baby;

class Player : public MonoBehaviour
{
public:
	void Awake()                         override;
	void Start()                         override;
	void Update(float deltaTime)         override;

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerStay(Collider* other)  override;
	void OnTriggerExit(Collider* other)  override;




	//Getter Setter

	
	//void SetState(State ste);
	//void SetAction(Action act);
	//void SetVisible(Visibilty vib);
	//
	//State GetState() { return state; }
	//Action GetAction() { return action; }

	Visibilty GetVisible() { return visibilty; };

	float GetFullness() { return m_fullness; }

	int GetHp() { return m_hp; }
	void SetHp(int hp) { m_hp = hp; }




	void FeedBaby(float bop);

	friend class PlayerController;
	friend class PlayerAnimator;
	friend class PlayerSound;

	void OnInspectorGUI() override;


private:
	int     m_hp			= 3;
	float   m_spd			= 500.0f;
	//float m_starv_level   = 500.0f;
	int		m_ivc_T		    = 15;						//fps 기준

	float	m_fullness;

	float m_elapsedTime = 0.f;


	float   m_baseSpd = 500.f;   // 기본 이동속도
	float   m_minSpd = 50.f;    // 최저 속도
	float   m_weightDivisor = 300.f;   // weightMult = 1 + w / Divisor

	static int invincible_Count;

	State		state		= State::Alive;
	Action		action		= Action::Idle;
	Visibilty	visibilty	= Visibilty::Visible;

	BoxCollider* m_boxCol = nullptr;
	Inventory* m_Inven = nullptr;
	Baby* m_baby = nullptr;
};

