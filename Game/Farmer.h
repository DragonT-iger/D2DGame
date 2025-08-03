#pragma once
class Farmer : public MonoBehaviour
{
	void Awake() override;

	void Start() override;
	
	void Update(float deltaTime) override;

    void PickRandomDirection();

	//애니메이션

	//AI


private:
    enum class State
    {
        Idle,
        Run,
        Attack
    };

    Animator* m_animator = nullptr;
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
    BoxCollider* m_boxCollider = nullptr;

    State   m_state = State::Idle;
    Vector2 m_direction = Vector2::zero;
    float   m_speed = 100.f;
    float   m_dirTimer = 0.f;
    float   m_dirInterval = 2.f;



    Vector2 m_initalPosition;



    //GameObject* farmerArea[4]; // patrol , chase , alert , attack;
    //float areaRadius[4] = { 350, 500, 300 ,200 };
    GameObject* patrolObject;  float patrolAreaValue = 350.0f;
    GameObject* chaseObject;  float chaseAreaValue = 500.0f;
    GameObject* alertObject;   float alertAreaValue = 300.0f;
    GameObject* attackObject;  float attackAreaValue = 200.0f;

};

