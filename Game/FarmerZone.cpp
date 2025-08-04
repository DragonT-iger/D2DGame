#include "pch.h"
#include "FarmerZone.h"
#include "Farmer.h"

void FarmerZone::Awake()
{
	GetOwner()->AddComponent<CircleCollider>()->SetRadius(m_circleColliderRadius);
}

void ChaseZone::OnTriggerEnter(Collider* other)
{
}

void ChaseZone::OnTriggerExit(Collider* other)
{
}

void AttackZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {
		m_farmer->ChangeState(Farmer::FarmerState::Attack);
	}
}

void AttackZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {
		if (m_farmer->m_isAlreadyExitChaseZone == false) {
			m_farmer->ChangeState(Farmer::FarmerState::Chase);
		}
		else {
			m_farmer->ChangeState(Farmer::FarmerState::Patrol);
		}
		m_farmer->m_hasPatrolTarget = false;
	}
}

void AlertZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {
		if (m_farmer->m_isAlreadyExitChaseZone == false) {
			m_farmer->ChangeState(Farmer::FarmerState::Chase);
		}
		else {
			m_farmer->ChangeState(Farmer::FarmerState::Patrol);
		}
		m_farmer->m_hasPatrolTarget = false;
	}
}

void AlertZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {
		m_farmer->ChangeState(Farmer::FarmerState::Patrol);
	}
}

void PatrolZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Farmer") {
		m_farmer->m_isAlreadyExitChaseZone = false;
	}
}

void PatrolZone::OnTriggerExit(Collider* other)
{
}
