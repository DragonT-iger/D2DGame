#pragma once
class Farmer : public MonoBehaviour
{
    enum class FarmerState
    {
        Patrol,
        Alert,
        Chase,
        Attack
    };
    FarmerState m_farmerState = FarmerState::Patrol;

	void Awake() override;

	void Start() override;
	
	void Update(float deltaTime) override;

public:
    //void PickRandomDirection();

    void DoPatrol(float deltaTime);
    void DoAlert(float deltaTime);
    void DoChase(float deltaTime);
    void DoAttack(float deltaTime);

	//애니메이션

	//AI


private:

    void OnInspectorGUI() override;

    const char* ToString(FarmerState   s) const;
    

    Animator* m_animator = nullptr;
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
    BoxCollider* m_boxCollider = nullptr;

    Vector2 m_direction = Vector2::zero;
    float   m_speed = 100.f;
    float   m_dirTimer = 0.f;
    float   m_dirInterval = 2.f;



    //patrol
    bool m_hasPatrolTarget = false;


    Vector2 m_initialPosition;
    Vector2 m_patrolTarget; 
    float   m_patrolBiasExp = 2.f;
    GameObject* patrolObject;  float m_patrolAreaValue = 350.0f;

    GameObject* chaseObject;  float m_chaseAreaValue = 500.0f;
    GameObject* alertObject;   float m_alertAreaValue = 300.0f;
    GameObject* attackObject;  float m_attackAreaValue = 200.0f;

};

