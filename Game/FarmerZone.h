#pragma once

class Farmer;

class FarmerZone : public MonoBehaviour
{
public:

    void Initalize(Farmer* farmer, float radius) { m_farmer = farmer; m_circleColliderRadius = radius;}
    void Awake() override;

private:
    Farmer* m_farmer = nullptr;   // 이벤트를 보낼 대상
    float m_circleColliderRadius = 0.0f;    
};
    

class PatrolZone : public FarmerZone {
    
};

class AlertZone : public FarmerZone {

};

class ChaseZone : public FarmerZone {

};

class AttackZone : public FarmerZone {

};