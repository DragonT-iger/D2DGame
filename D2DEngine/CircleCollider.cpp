#include "pch.h"
#include "CircleCollider.h"

bool CircleCollider::IsCollide(const Collider* other) const
{
		// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
		//circle->GetCenter() + circle->GetRadius();


		//std::cout << circle->GetCenter().x << " " << circle->GetCenter().y << " " << circle->m_radius << std::endl;
		

		
		float length = abs(pow(GetCenter().x - circle->GetCenter().x, 2) + pow(GetCenter().y - circle->GetCenter().y, 2));


		if(circle->GetRadius() * 200 + m_radius * 200 >= length) // 임의 반지름 값 일단
		{
			return true;
		}



		//GetOwner()->

		return false;
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

		//이거는 다음 수업시간에 알려주시니까 그걸로 하고 Physics Manager (씬에서 게임오브젝트로 돌리는거)는 그때 같이 구현

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();

	}


	//정의되지 않은 나머지는 충돌하지 않음
	return false;
}
