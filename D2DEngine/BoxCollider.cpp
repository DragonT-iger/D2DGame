#include "pch.h"
#include "BoxCollider.h"

bool BoxCollider::IsCollide(const Collider* other) const
{
	// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

		//�̰Ŵ� ���� �����ð��� �˷��ֽôϱ� �װɷ� �ϰ� Physics Manager (������ ���ӿ�����Ʈ�� �����°�)�� �׶� ���� ����

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();
	}

	return false;
}
