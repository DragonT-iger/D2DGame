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

		//�̰Ŵ� ���� �����ð��� �˷��ֽôϱ� �װɷ� �ϰ� Physics Manager (������ ���ӿ�����Ʈ�� �����°�)�� �׶� ���� ����

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();

	}


	return true;


	//���ǵ��� ���� �������� �浹���� ����
	return false;
}

void CircleCollider::CreateFixture()
{
    // 1) �ٵ� �غ� �� Rigidbody2D �� ������ ����, ������ ���� �ٵ� ����
    b2Body* body = nullptr;

    if (auto* rb = GetOwner()->GetComponent<Rigidbody2D>())
    {
        body = rb->GetBody();                 // ���� �ٵ� ��Ȱ��
    }
    else
    {
        b2BodyDef bd{};
        bd.type = b2_staticBody;               // �⺻�� ���� Ʈ����
        auto pos = m_transform->GetPosition();
        bd.position.Set(pos.x, pos.y);
        body = PhysicsManager::Instance().CreateBody(bd);
    }

    // 2) �� ���� ����
    b2CircleShape shape;
    shape.m_p.Set(m_offset.x, m_offset.y);     // ������ ����
    shape.m_radius = m_radius;                // ���� ������

    // 3) �Ƚ�ó ����
    b2FixtureDef fd{};
    fd.shape = &shape;
    fd.isSensor = m_isTrigger;                // Ʈ���� ����

    m_fixture = body->CreateFixture(&fd);

    // 4) Box2D �� Collider* ���� (ContactListener ���� ���)
    m_fixture->GetUserData().pointer =
        reinterpret_cast<uintptr_t>(this);
}