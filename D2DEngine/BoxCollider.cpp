#include "pch.h"
#include "BoxCollider.h"

bool BoxCollider::IsCollide(const Collider* other) const
{
	// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

		//이거는 다음 수업시간에 알려주시니까 그걸로 하고 Physics Manager (씬에서 게임오브젝트로 돌리는거)는 그때 같이 구현

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();
	}

	return false;
}
