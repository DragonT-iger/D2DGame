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


		if(circle->GetRadius() * 200 + m_radius * 200 >= length) // ���� ������ �� �ϴ�
		{
			return true;
		}



		//GetOwner()->

		return false;
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

		//�̰Ŵ� ���� �����ð��� �˷��ֽôϱ� �װɷ� �ϰ� Physics Manager (������ ���ӿ�����Ʈ�� �����°�)�� �׶� ���� ����

	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();

	}


	//���ǵ��� ���� �������� �浹���� ����
	return false;
}
