#include "pch.h"
#include "BoxCollider.h"


bool BoxCollider::IsCollide(const Collider* other) const
{
	// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
	}
	else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other)) {

		Vector2 thisCenter = GetCenter();
		Vector2 leftdown = thisCenter - size / 2;
		Vector2 rightup = thisCenter + size / 2;

		Vector2 otherCenter = box->GetCenter();
		Vector2 otherLeftdown = otherCenter - box->GetSize() / 2;
		Vector2 otherRightup = otherCenter + box->GetSize() / 2;

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
	D2DRenderer::Instance().DrawRectangle(-size.x / 2, -size.y / 2, size.x / 2, size.y / 2, D2D1::ColorF(1.f, 0.f, 0.f));
}
