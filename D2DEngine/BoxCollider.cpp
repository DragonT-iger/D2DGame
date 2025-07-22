#include "pch.h"
#include "BoxCollider.h"


//bool BoxCollider::IsCollide(const Collider* other) const
//{
//	// Circle vs Circle collision detection logic
//	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
//	{
//
//	}
//	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
//		//CircletoBox();
//	}
//	return true;
//	return false;
//}

// BoxCollider.cpp --------------------------
void BoxCollider::CreateFixture()
{
    constexpr float PPM = 100.f;          // pixel-per-meter

    b2Body* body = nullptr;
    if (auto* rb = GetOwner()->GetComponent<Rigidbody2D>())
        body = rb->GetBody();             // 동적/키네마틱 바디 재사용
    else {
        b2BodyDef bd{};
        bd.type = b2_staticBody;
        auto p = m_transform->GetPosition();
        bd.position.Set(p.x / PPM, p.y / PPM);
        body = PhysicsManager::Instance().Get()->CreateBody(&bd);
    }

    b2PolygonShape shape;
    shape.SetAsBox(size.x * 0.5f / PPM, size.y * 0.5f / PPM);

    b2FixtureDef fd{};
    fd.shape = &shape;
    fd.isSensor = m_isTrigger;

    m_fixture = body->CreateFixture(&fd);
    m_fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

