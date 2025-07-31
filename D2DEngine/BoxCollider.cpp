#include "pch.h"
#include "BoxCollider.h"
#include <algorithm>


void BoxCollider::Awake()
{
	Collider::Awake();

	if (auto sr = GetComponent<SpriteRenderer>())
		size = { sr->GetSize().width, sr->GetSize().height };
}

bool BoxCollider::IsCollide(const Collider* other) const
{
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
		Vector2 scale = circle->GetComponent<Transform>()->GetScale();
		Vector2 clampCirclePos = circle->GetCenter();

		Vector2 otherCenter = other->GetCenter();
		Vector2 otherScale = other->GetComponent<Transform>()->GetScale();
		Vector2 otherLeftDown = otherCenter - size * otherScale / 2 ;
		Vector2 otherRightUp = otherCenter + size * otherScale / 2 ;



		clampCirclePos.x = std::clamp(clampCirclePos.x, otherLeftDown.x, otherRightUp.x);
		clampCirclePos.y = std::clamp(clampCirclePos.y, otherLeftDown.y, otherRightUp.y);


		float SquareLength = (circle->GetCenter() - clampCirclePos).SqrMagnitude();

		if (SquareLength < (circle->GetRadius() * circle->GetRadius())) {
			return true;
		};
		
		return false;

		//if(clampCirclePos.x , other->GetCenter().x 




	}
	else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other)) {

		Vector2 scale = GetComponent<Transform>()->GetScale();
		Vector2 thisCenter = GetCenter();
		Vector2 leftdown = thisCenter - size / 2 * scale;
		Vector2 rightup = thisCenter + size / 2 * scale;

		Vector2 otherScale = box->GetComponent<Transform>()->GetScale();
		Vector2 otherCenter = box->GetCenter();
		Vector2 otherLeftdown = otherCenter - box->GetSize() / 2 * otherScale;
		Vector2 otherRightup = otherCenter + box->GetSize() / 2 * otherScale;

		// 충돌 검사
		if (leftdown.x < otherRightup.x && rightup.x > otherLeftdown.x &&
			leftdown.y < otherRightup.y && rightup.y > otherLeftdown.y)
		{
			return true; 
		}

		
	}
	//return true;
	return false;
}

void BoxCollider::DrawCollider()
{
	D2DRenderer::Instance().DrawRectangle((- size.x / 2) + m_offset.x, (-size.y / 2) + m_offset.y, (size.x / 2)+ m_offset.x, (size.y / 2) + m_offset.y, D2D1::ColorF(1.f, 0.f, 0.f));
}
