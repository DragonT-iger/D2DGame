#include "pch.h"
#include "BoxCollider.h"


bool BoxCollider::IsCollide(const Collider* other) const
{
	// Circle vs Circle collision detection logic
	if (const CircleCollider* circle = dynamic_cast<const CircleCollider*>(other))
	{
	}
	else if (const BoxCollider* circle = dynamic_cast<const BoxCollider*>(other)) {
		//CircletoBox();
	}
	//return true;
	return false;
}

void BoxCollider::DrawCollider()
{
	D2DRenderer::Instance().DrawRectangle(-size.x / 2, -size.y / 2, size.x / 2, size.y / 2, D2D1::ColorF(1.f, 0.f, 0.f));
}
