#include "pch.h"
#include "CircleCollider.h"

bool CircleCollider::IsCollide(const Collider* other) const
{
		// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
		//circle->GetCenter() + circle->GetRadius();

		//constexpr float PPM = 50.0f;
		//std::cout << circle->GetCenter().x << " " << circle->GetCenter().y << " " << circle->m_radius * PPM << " " << GetCenter().x << " " << GetCenter().y << " " << m_radius * PPM << std::endl;
				
		float squareLength = (pow(GetCenter().x - circle->GetCenter().x, 2) + pow(GetCenter().y - circle->GetCenter().y, 2));

		//std::cout << circle->GetRadius() + m_radius << " " << length << std::endl;
		if (pow((circle->GetRadius() + m_radius), 2) >= squareLength) // 임의 반지름 값 일단
		{
			return true;
		}



		//GetOwner()->

		return false;
		//other->GetOffset() + other->GetOwner()->GetComponent<Transform>() * other->GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	

	}
	else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();

		Vector2 scale = GetComponent<Transform>()->GetScale();
		Vector2 clampCirclePos = GetCenter();

		Vector2 otherCenter = box->GetCenter();
		Vector2 otherScale = box->GetComponent<Transform>()->GetScale();
		Vector2 otherLeftDown = otherCenter - box->GetSize() * otherScale / 2 ;
		Vector2 otherRightUp = otherCenter + box->GetSize() * otherScale / 2 ;



		clampCirclePos.x = std::clamp(clampCirclePos.x, otherLeftDown.x, otherRightUp.x);
		clampCirclePos.y = std::clamp(clampCirclePos.y, otherLeftDown.y, otherRightUp.y);


		float SquareLength = (GetCenter() - clampCirclePos).SqrMagnitude();

		if (SquareLength < GetRadius() * GetRadius()) {
			return true;
		};

		return false;
		

	}


	//정의되지 않은 나머지는 충돌하지 않음
	return false;
}

void CircleCollider::DrawCollider()
{
	D2DRenderer::Instance().DrawCircle(0.f, 0.f, m_radius, D2D1::ColorF(1.f, 0.f, 0.f));
}

ColliderInfo CircleCollider::GetColliderInfo()
{
	return { m_transform, this };
}
