#pragma once

enum class State
{
	Alive,
	Starve,
	Killed
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
	void SetAction(Action act);
	//void SetVisible(Visibilty vib);
	State GetState() { return state; }
	Action GetAction() { return action; }
	Visibilty GetVisible() { return visibilty; };

	int GetFullness() { return m_fullness; }

	int GetHp() { return m_hp; }
	void SetHp(int hp);
	bool GetHittable() { return m_isHittable; }


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

	std::vector<GameObject*> m_hpUI;

	int		m_fullness;
	UINT	m_maxFullness = 1500;

	float m_elapsedTime = 0.f;

	float   m_minSpd = 50.f;   
	float   m_weightDivisor = 300.f;  

	float m_invincible_Count;
	bool m_isHittable = true;

	std::array<size_t, 3> maxCount = { 100, 60, 15 };//감자, 가지, 호박 순

	State		state		= State::Alive;
	Action		action		= Action::Idle;
	Visibilty	visibilty	= Visibilty::Visible;

	//Animator* m_animtor = nullptr;
	PlayerAnimator* m_P_animator = nullptr;
	SpriteRenderer* m_P_spriteRen = nullptr;
	BoxCollider* m_boxCol = nullptr;
	Inventory* m_Inven = nullptr;
	Baby* m_baby = nullptr;

	PlayerSound* m_pSound;
};

