#pragma once
class Farmer : public MonoBehaviour
{

	void Awake() override;

	void Start() override;
	
	void Update(float deltaTime) override;

public:

    enum class FarmerState
    {
        Patrol,
        Alert,
        Chase,
        Attack
    };
    FarmerState m_farmerState = FarmerState::Patrol;
    //void PickRandomDirection();

    void DoPatrol(float deltaTime);
    void DoAlert(float deltaTime);
    void DoChase(float deltaTime);
    void DoAttack(float deltaTime);

    void ChangeState(FarmerState farmerState);

	//애니메이션

	//AI

    void OnTriggerExit(Collider* other) override;




    bool m_isAlreadyExitChaseZone = false;

private:

#ifdef _DEBUG
    void OnInspectorGUI() override;
#endif // _DEBUG
    const char* ToString(FarmerState   s) const;
    
    //component
    Animator* m_animator = nullptr;
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
    BoxCollider* m_boxCollider = nullptr;

    Vector2 m_direction = Vector2::zero;
    float   m_speed = 100.f;


    GameObject* m_player;


    //patrol
    bool m_hasPatrolTarget = false;
    Vector2 m_initialPosition;
    Vector2 m_patrolTarget; 
    float   m_patrolBiasExp = 2.f;

    //attack
    


    GameObject* patrolObject;  float m_patrolAreaValue = 350.0f;
    GameObject* chaseObject;  float m_chaseAreaValue = 650.0f;
    GameObject* alertObject;   float m_alertAreaValue = 300.0f;
    GameObject* attackObject;  float m_attackAreaValue = 200.0f;

};

