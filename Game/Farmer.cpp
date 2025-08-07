#include "pch.h"
#include "Farmer.h"
#include "FarmerZone.h"
#include "YSort.h"
#include "Player.h"

#include "AttackEffect.h"

void Farmer::Awake()
{
    m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();
	m_animator = GetOwner()->AddComponent<Animator>();
    m_transform = GetComponent<Transform>();
    m_transform->SetScale({ 0.35f, 0.35f });
    m_boxCollider = GetOwner()->AddComponent<BoxCollider>();
    m_player = SceneManager::Instance().GetActiveScene()->GetPlayer();
    this->GetOwner()->SetTag("Farmer");
    GetOwner()->AddComponent<YSort>()->SetStatic(false);
}

void Farmer::Start()
{

    m_boxCollider->SetOffset({ 4.0f, 0.0f });
    m_boxCollider->SetSize({ 140.0f , 400.0f });

	auto idle = ResourceManager::Instance().LoadAnimationClip("farmer_final.json", "idle");
    auto angryidle = ResourceManager::Instance().LoadAnimationClip("farmer_final.json", "angryidle");
    auto walk = ResourceManager::Instance().LoadAnimationClip("farmer_final.json", "walk");
    auto angrywalk = ResourceManager::Instance().LoadAnimationClip("farmer_final.json", "angrywalk");
	auto attack = ResourceManager::Instance().LoadAnimationClip("farmer_final.json", "attack");

    m_animator->AddClip("idle", idle, true); 
    m_animator->AddClip("angryidle", angryidle, true);
	m_animator->AddClip("walk", walk, true);
    m_animator->AddClip("angrywalk", angrywalk, true);
    m_animator->AddClip("attack", attack, false);
    

	m_animator->SetEntryState("idle");

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

    m_attackPattern.SetOffsets({
     {0.f, 0.f},
     //{m_attackAreaValue, 0.f},
     //{-m_attackAreaValue, 0.f},
     {0.f, m_attackAreaValue},
     {0.f, -m_attackAreaValue}
        });
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

        m_patrolTarget = {
            m_initialPosition.x + std::cos(rad) * r,
            m_initialPosition.y + std::sin(rad) * r
        };
        /*if (m_patrolTarget.x - cur.x > 0) m_spriteRenderer->SetFlip(false);
        if (m_patrolTarget.x - cur.x < 0) m_spriteRenderer->SetFlip(true);*/
    }


    if (m_patrolTarget.x - cur.x > 0) m_spriteRenderer->SetFlip(false);
    if (m_patrolTarget.x - cur.x < 0) m_spriteRenderer->SetFlip(true);

    /* ---- 이동 ---- */
    Vector2 dir = m_patrolTarget - cur;
    if (dir.SqrMagnitude() > 0.1f)
    {
        dir.Normalize();
        m_transform->Translate(dir * m_speed * deltaTime); 

        if(m_animator->GetCurState() != "walk")
            m_animator->ChangeState("walk");
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
    if (m_player->GetComponent<Player>()->GetVisible() == Visibilty::Hide) {
        ChangeState(FarmerState::Patrol);
    }

    if (m_animator->GetCurState() != "angrywalk")
        m_animator->ChangeState("angrywalk");

    Vector2 dir = m_player->GetComponent<Transform>()->GetPosition()
        - m_transform->GetPosition();

    dir.Normalize();

    m_transform->Translate(dir * m_speed * deltaTime);

    if (dir.x < 0) { m_spriteRenderer->SetFlip(true); }
    if (dir.x > 0) { m_spriteRenderer->SetFlip(false); }
}

void Farmer::DoAttack(float deltaTime)
{
    if (m_player->GetComponent<Player>()->GetVisible() == Visibilty::Hide) {
        m_attackPattern.ClearIndicators();
        ChangeState(FarmerState::Patrol);
        return;
    }

    if (m_animator->GetCurState() == "attack" && !m_animator->IsAnimeEnd()) {
        return;
    }
    else if(m_animator->GetCurState() == "attack"){
        if (m_isAlreadyExitAttackZone == true) {
            ChangeState(FarmerState::Chase);
        }
        else {
            ChangeState(FarmerState::Attack);
        }
    }
    if (m_animator->GetCurState() != "angryidle") {
        m_animator->ChangeState("angryidle");
    }


    // 만약 attack play 중이면 return

    

    if (m_player->GetComponent<Transform>()->GetPosition().x - m_transform->GetPosition().x > 0) {
        m_spriteRenderer->SetFlip(false);
    }
    else if (m_player->GetComponent<Transform>()->GetPosition().x - m_transform->GetPosition().x < 0) {
        m_spriteRenderer->SetFlip(true);
    }
    

    if (!m_attackPattern.HasIndicators()) {
        m_attackIntervalTimer += deltaTime;
        if (m_attackIntervalTimer >= m_attackInterval) {
            m_attackIntervalTimer = 0.f;
            m_attackPattern.CreateIndicators(this, m_player->GetComponent<Transform>()->GetPosition(), m_attackAreaValue);
            
            m_attackTimer = 0.f;
        }
    }
    else {
        m_attackTimer += deltaTime;
        if (m_attackTimer >= m_attackDelay) {
            m_attackPattern.Execute(m_player->GetComponent<Transform>()->GetPosition(), m_attackAreaValue);
            m_player->GetComponent<Player>()->SetHp(m_player->GetComponent<Player>()->GetHp() - 1);
            m_animator->ChangeState("attack");
        }
    }
    
}

void Farmer::ChangeState(FarmerState farmerState)
{
    if (m_farmerState == FarmerState::Attack && farmerState != FarmerState::Attack) {
        m_attackPattern.ClearIndicators();
    }
    if (m_animator->GetCurState() == "patrol") {
        m_hasPatrolTarget = false;
    }
    if (farmerState == FarmerState::Attack) {
        m_attackPattern.ClearIndicators();

        m_attackTimer = 0.f;
        m_attackIntervalTimer = 0.f;
    }
    m_farmerState = farmerState;
}



void Farmer::OnTriggerExit(Collider* other)
{
    if (other->GetOwner() == chaseObject) {
        ChangeState(FarmerState::Patrol);
        m_isAlreadyExitChaseZone = true;
        Vector2 pos = m_transform->GetPosition();
        if (m_transform->GetPosition().x - m_patrolTarget.x > 0) {
            m_spriteRenderer->SetFlip(true);
        }
        else if (m_transform->GetPosition().x - m_patrolTarget.x < 0) {
            m_spriteRenderer->SetFlip(false);
        }
    }
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
    std::string curAnim = m_animator->GetCurState();
    ImGui::Text("AI   : %s", ToString(m_farmerState));
    ImGui::Text("Anim : %s", curAnim.c_str());
    ImGui::Separator();

    ImGui::DragFloat("Move Speed", &m_speed, 1.f);
    ImGui::DragFloat("Patrol Bias", &m_patrolBiasExp, 0.1f, 0.1f, 20.f);
    ImGui::DragFloat("AttackInterval", &m_attackInterval, 0.01f, 0.1f, 10.f);
    ImGui::DragInt("AttackIndicatorCount", &m_attackIndicatorCount);
    ImGui::Checkbox("m_isAlreadyExitChaseZone", &m_isAlreadyExitChaseZone);
    ImGui::Checkbox("m_isAlreadyExitAttackZone", &m_isAlreadyExitAttackZone);
    //m_hasPatrolTarget

    //ImGui::Checkbox("hasPatrolTarget", &m_hasPatrolTarget);

    bool areaChanged = false;

    areaChanged |= ImGui::DragFloat("Patrol Radius", &m_patrolAreaValue, 1.f, 10.f, 2000.f);
    areaChanged |= ImGui::DragFloat("Chase  Radius", &m_chaseAreaValue, 1.f, 10.f, 2000.f);
    areaChanged |= ImGui::DragFloat("Alert  Radius", &m_alertAreaValue, 1.f, 10.f, 2000.f);
    areaChanged |= ImGui::DragFloat("Attack Radius", &m_attackAreaValue, 1.f, 10.f, 2000.f);

    if (areaChanged)
    {
        if (auto c = patrolObject->GetComponent<CircleCollider>()) c->SetRadius(m_patrolAreaValue);
        if (auto c = chaseObject->GetComponent<CircleCollider>()) c->SetRadius(m_chaseAreaValue);
        if (auto c = alertObject->GetComponent<CircleCollider>()) c->SetRadius(m_alertAreaValue);
        if (auto c = attackObject->GetComponent<CircleCollider>()) c->SetRadius(m_attackAreaValue);
    }
}

#endif
