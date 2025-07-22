#include "pch.h"
#include "CircleCollider.h"
#include "Rigidbody2D.h"

bool CircleCollider::IsCollide(const Collider* other) const
{
		// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{

		return true;
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

		//이거는 다음 수업시간에 알려주시니까 그걸로 하고 Physics Manager (씬에서 게임오브젝트로 돌리는거)는 그때 같이 구현

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();

	}


	return true;


	//정의되지 않은 나머지는 충돌하지 않음
	return false;
}

void CircleCollider::CreateFixture()
{
    // 1) 바디 준비 ─ Rigidbody2D 가 있으면 재사용, 없으면 정적 바디 생성
    b2Body* body = nullptr;

    if (auto* rb = GetOwner()->GetComponent<Rigidbody2D>())
    {
        body = rb->GetBody();                 // 동적 바디 재활용
    }
    else
    {
        b2BodyDef bd{};
        bd.type = b2_staticBody;               // 기본은 정적 트리거
        auto pos = m_transform->GetPosition();
        bd.position.Set(pos.x, pos.y);
        body = PhysicsManager::Instance().CreateBody(bd);
    }

    // 2) 원 형상 정의
    b2CircleShape shape;
    shape.m_p.Set(m_offset.x, m_offset.y);     // 오프셋 적용
    shape.m_radius = m_radius;                // 실제 반지름

    // 3) 픽스처 생성
    b2FixtureDef fd{};
    fd.shape = &shape;
    fd.isSensor = m_isTrigger;                // 트리거 여부

    m_fixture = body->CreateFixture(&fd);

    // 4) Box2D → Collider* 매핑 (ContactListener 에서 사용)
    m_fixture->GetUserData().pointer =
        reinterpret_cast<uintptr_t>(this);
}