#include "pch.h"
#include "Rigidbody2D.h"

static constexpr float PPM = 100.0f; // Pixel to Meter

void Rigidbody2D::Awake() {
    Transform* tr = GetComponent<Transform>();
    assert(tr && "Rigidbody2D requires Transform");

    b2BodyDef def;
    def.position.Set(tr->GetPosition().x / PPM, tr->GetPosition().y / PPM);
    def.angle = tr->GetRotation();
    switch (m_bodyType) {
        case BodyType::Static:   def.type = b2_staticBody;   break;
        case BodyType::Kinematic:def.type = b2_kinematicBody; break;
        case BodyType::Dynamic:  def.type = b2_dynamicBody;  break;
    }

    m_body = PhysicsManager::Instance().CreateBody(def);
    m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

void Rigidbody2D::FixedUpdate(float fixedDelta) {
    assert(m_body && "Body가 생성되지 않음");
    auto pos = m_body->GetPosition();
    auto angle = m_body->GetAngle();

    Transform* tr = GetComponent<Transform>();
    tr->SetPosition({ pos.x * PPM, pos.y * PPM });
    tr->SetRotation(angle);
}
