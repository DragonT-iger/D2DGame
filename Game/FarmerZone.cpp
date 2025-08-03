#include "pch.h"
#include "FarmerZone.h"

void FarmerZone::Awake()
{
	GetOwner()->AddComponent<CircleCollider>()->SetRadius(m_circleColliderRadius);
}
