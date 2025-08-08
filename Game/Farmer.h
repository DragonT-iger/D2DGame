#pragma once
#include "AttackPattern.h"
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

    void DoPatrol(float deltaTime);
    void DoAlert(float deltaTime);
    void DoChase(float deltaTime);
    void DoAttack(float deltaTime);

    void ChangeState(FarmerState farmerState);



   

	//애니메이션
    FarmerState GetFarmerState() { return m_farmerState; }


	//AI
    std::vector<Vector2> GenerateRandomAttackOffsets(float radius);



    void OnTriggerExit(Collider* other) override;



    bool m_isAlreadyExitAttackZone = true;
    bool m_isAlreadyExitAlertZone = true;
    bool m_isAlreadyExitChaseZone = true;
    bool m_hasPatrolTarget = false;
    bool m_isCommonAttackIndicatorArea = false;
    int  m_attackIndicatorCount = 0;
    bool m_hasDamagedPlayer = false;


private:

    FarmerState m_farmerState = FarmerState::Patrol;
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
    float   m_speed = 250.f;


    GameObject* m_player;


    //patrol
    Vector2 m_initialPosition;
    Vector2 m_patrolTarget; 
    float   m_patrolBiasExp = 2.f;

    //attack
    


    GameObject* patrolObject;  float m_patrolAreaValue = 600.0f;
    GameObject* chaseObject;  float m_chaseAreaValue = 1100.0f;
    GameObject* alertObject;   float m_alertAreaValue = 700.0f;
    GameObject* attackObject;  float m_attackAreaValue = 450.0f;


    //GameObject* m_attackIndicator = nullptr;
    float       m_attackDelay = 1.0f;
    float       m_attackTimer = 0.0f;   
    float       m_attackInterval = 0.5f;
    float       m_attackIntervalTimer = 0.0f;

    

    AttackPattern m_attackPattern;
};

