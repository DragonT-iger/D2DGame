#include "pch.h"
#include "Farmer.h"

void Farmer::Awake()
{
    m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();
	m_animator = GetOwner()->AddComponent<Animator>();
    m_transform = GetComponent<Transform>();
    m_transform->SetScale({ 0.35f, 0.35f });
    m_boxCollider = GetOwner()->AddComponent<BoxCollider>();

    
}

void Farmer::Start()
{

    m_boxCollider->SetOffset({ 4.0f, 0.0f });
    m_boxCollider->SetSize({ 140.0f , 400.0f });

	auto idle = ResourceManager::Instance().LoadAnimationClip("farmertest2.json", "idle");
	auto run = ResourceManager::Instance().LoadAnimationClip("farmertest2.json", "run");
	auto attack = ResourceManager::Instance().LoadAnimationClip("farmertest2.json", "attack");

	m_animator->AddClip("idle", idle, true);
	m_animator->AddClip("run", run, true);
	m_animator->AddClip("attack", attack, false);

	m_animator->SetEntryState("idle");
	//m_animator->ChangeState("idle");
	PickRandomDirection();



    //SetInitalPosition
    m_initalPosition = m_transform->GetPosition();

    patrolArea = Instantiate("PatrolArea");
    patrolArea->AddComponent<CircleCollider>()->SetRadius(patrolAreaValue);
    patrolArea->GetComponent<Transform>()->SetPosition(m_initalPosition);
    //auto AreaComponent = patrolArea->AddComponent<PatrolArea>();


    chaseArea = Instantiate("ChaseArea");
    chaseArea->AddComponent<CircleCollider>()->SetRadius(chaseAreaValue);
    chaseArea->GetComponent<Transform>()->SetPosition(m_initalPosition);
    //auto AreaComponent = chaseArea->AddComponent<ChaseArea>();
    
    alertArea = Instantiate("AlertArea");
    alertArea->AddComponent<CircleCollider>()->SetRadius(alertAreaValue);
    alertArea->GetComponent<Transform>()->SetParent(m_transform);
    //auto AreaComponent = alertArea->AddComponent<AlertArea>();

    attackArea = Instantiate("AttackArea");
    attackArea->AddComponent<CircleCollider>()->SetRadius(attackAreaValue);
    attackArea->GetComponent<Transform>()->SetParent(m_transform);
    //auto AreaComponent = attackArea->AddComponent<AttackArea>();

    /*AttackRangeObject->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

    AttackRangeObject->GetComponent<Transform>()->SetScale({ 1,1 });*/


}

void Farmer::PickRandomDirection()
{
    int r = Random::Instance().Range(0, 5);
    switch (r)
    {
    case 0: m_direction = Vector2::zero;  break;
    case 1: m_direction = Vector2::left;  break;
    case 2: m_direction = Vector2::right; break;
    case 3: m_direction = Vector2::up;    break;
    case 4: m_direction = Vector2::down;  break;
    }
    if (m_direction.x > 0) {
        m_spriteRenderer->SetFlip(false);
    }
    else if(m_direction.x < 0) {
        m_spriteRenderer->SetFlip(true);
    }
}

void Farmer::Update(float deltaTime)
{


    //std::cout << m_transform->GetPosition().x << " " << m_transform->GetPosition().y << std::endl;

    //std::cout << AttackRangeObject->GetComponent<Transform>()->GetPosition().x << std::endl;
    m_dirTimer += deltaTime;
    if (m_dirTimer > m_dirInterval)
    {
        PickRandomDirection();
        m_dirTimer = 0.f;
    }

    if (Input.GetKeyDown(Keycode::SPACE))
    {
        m_state = State::Attack;
        m_animator->ChangeState("attack");
    }

    if (m_state == State::Attack)
    {
        if (m_animator->IsAnimeEnd())
        {
            m_state = State::Idle;
            m_animator->ChangeState("idle");
        }
        return;
    }

    if (m_direction != Vector2::zero)
    {
        m_transform->Translate(m_direction * m_speed * deltaTime);
        if (m_state != State::Run)
        {
            m_animator->ChangeState("run");
            m_state = State::Run;
        }
    }
    else
    {
        if (m_state != State::Idle)
        {
            m_animator->ChangeState("idle");
            m_state = State::Idle;
        }
    }
}



//void Farmer
