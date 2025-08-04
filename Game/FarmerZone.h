#pragma once

class Farmer;

class FarmerZone : public MonoBehaviour
{
public:

    void Initalize(Farmer* farmer, float radius) { m_farmer = farmer; m_circleColliderRadius = radius;}
    void Awake() override;

protected:
    Farmer* m_farmer = nullptr;   // 이벤트를 보낼 대상
    float m_circleColliderRadius = 0.0f;    
};
    

class PatrolZone : public FarmerZone {
    void OnTriggerEnter(Collider* other) override;
    void OnTriggerExit(Collider* other) override;
};

class AlertZone : public FarmerZone {
    void OnTriggerEnter(Collider* other) override;
    void OnTriggerExit(Collider* other) override;
};

class ChaseZone : public FarmerZone {
    
    void OnTriggerEnter(Collider* other) override;
    void OnTriggerExit(Collider* other) override;
};

class AttackZone : public FarmerZone {
    void OnTriggerEnter(Collider* other) override;
    void OnTriggerExit(Collider* other) override;
};