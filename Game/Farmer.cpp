#include "pch.h"
#include "Farmer.h"
#include "FarmerZone.h"

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
	//PickRandomDirection();



    //SetInitalPosition
    m_initialPosition = m_transform->GetPosition();


    patrolObject = Instantiate("PatrolArea");
    patrolObject->GetComponent<Transform>()->SetPosition(m_initialPosition);
    auto patrolZone = patrolObject->AddComponent<PatrolZone>();
    patrolZone->Initalize(this, m_patrolAreaValue);

    chaseObject = Instantiate("ChaseArea");
    chaseObject->GetComponent<Transform>()->SetPosition(m_initialPosition);
    auto chaseZone = chaseObject->AddComponent<ChaseZone>();
    chaseZone->Initalize(this, m_chaseAreaValue);
    
    alertObject = Instantiate("AlertArea");
    alertObject->GetComponent<Transform>()->SetParent(m_transform);
    auto alertZone = alertObject->AddComponent<AlertZone>();
    alertZone->Initalize(this, m_alertAreaValue);

    attackObject = Instantiate("AttackArea");
    attackObject->GetComponent<Transform>()->SetParent(m_transform);
    auto attackZone = attackObject->AddComponent<AttackZone>();
    attackZone->Initalize(this, m_attackAreaValue);


}

void Farmer::Update(float deltaTime)
{
    switch (m_farmerState)
    {
        case FarmerState::Patrol: DoPatrol(deltaTime);  break;
        case FarmerState::Alert:  DoAlert(deltaTime);  break;
        case FarmerState::Chase:  DoChase(deltaTime);  break;
        case FarmerState::Attack: DoAttack(deltaTime);  break;
    }
}

void Farmer::DoPatrol(float deltaTime)
{
    Vector2 cur = m_transform->GetPosition();

    // 목표를 아직 못 잡았거나, 거의 도달했으면 새 목표 생성
    if (!m_hasPatrolTarget || (m_patrolTarget - cur).SqrMagnitude() < 4.f)
    {
        m_hasPatrolTarget = true;

        float rad = DirectX::XM_2PI * (Random::Instance().Range(0, 10001) / 10000.f);

        float t = Random::Instance().Range(0, 10001) / 10000.f;

        float biased = std::pow(t, m_patrolBiasExp); 

        float r = m_patrolAreaValue * biased;

        //if (cos(rad) < 0) m_spriteRenderer->SetFlip(true);
        //if (cos(rad) > 0) m_spriteRenderer->SetFlip(false);

        // 5) 목표 좌표
        m_patrolTarget = {
            m_initialPosition.x + std::cos(rad) * r,
            m_initialPosition.y + std::sin(rad) * r
        };
        if (m_patrolTarget.x - cur.x > 0) m_spriteRenderer->SetFlip(false);
        if (m_patrolTarget.x - cur.x < 0) m_spriteRenderer->SetFlip(true);
    }

    /* ---- 이동 ---- */
    Vector2 dir = m_patrolTarget - cur;
    if (dir.SqrMagnitude() > 0.1f)
    {
        dir.Normalize();
        m_transform->Translate(dir * m_speed * deltaTime); 

        if(m_animator->GetCurState() != "run")
            m_animator->ChangeState("run");
    }
    else
    {
        if (m_animator->GetCurState() != "idle")
            m_animator->ChangeState("idle");
    }
}


void Farmer::DoAlert(float deltaTime)
{
}

void Farmer::DoChase(float deltaTime)
{
}

void Farmer::DoAttack(float deltaTime)
{
}



#ifdef _DEBUG

const char* Farmer::ToString(FarmerState s) const
{
    switch (s)
    {
    case FarmerState::Patrol: return "Patrol";
    case FarmerState::Alert:  return "Alert";
    case FarmerState::Chase:  return "Chase";
    case FarmerState::Attack: return "Attack";
    default:                  return "Unknown";
    }
}

void Farmer::OnInspectorGUI()
{
    std::string animation_state = m_animator->GetCurState();
    ImGui::Text("AI  : %s", ToString(m_farmerState));
    ImGui::Text("Anim: %s", animation_state.c_str() );
    ImGui::Separator();

    ImGui::DragFloat("Move Speed", &m_speed, 1.f);
    ImGui::DragFloat("Bias", &m_patrolBiasExp , 0.1f, 0.1f, 20.0f); // 아 setter getter도 필요없었네 ㅋㅋㅋㅋ
}

#endif


//void Farmer
