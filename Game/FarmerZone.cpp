#include "pch.h"
#include "FarmerZone.h"
#include "Farmer.h"
#include "Player.h"

void FarmerZone::Awake()
{
	GetOwner()->AddComponent<CircleCollider>()->SetRadius(m_circleColliderRadius);
}

void ChaseZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
		m_farmer->m_isAlreadyExitChaseZone = false;
}

void ChaseZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
	{
		m_farmer->m_isAlreadyExitChaseZone = true; 

		//if (m_farmer->GetFarmerState() != Farmer::FarmerState::Attack)
		//	m_farmer->ChangeState(Farmer::FarmerState::Patrol);
	}
}

void AttackZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {


		if (Farmer::FarmerState::Attack != m_farmer->GetFarmerState()) {
			m_farmer->ChangeState(Farmer::FarmerState::Attack);
		}
		m_farmer->m_isAlreadyExitAttackZone = false;
	}

	
}

void AttackZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {
		m_farmer->m_isAlreadyExitAttackZone = true;
		if (m_farmer->GetFarmerState() == Farmer::FarmerState::Attack) {
			return;
		}
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

		if (m_farmer->GetFarmerState() == Farmer::FarmerState::Attack)
			return;

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

AttackIndicatorZone::~AttackIndicatorZone()
{
	if (!m_isPlayerInside || !m_farmer)
		return;

	if (m_farmer->m_attackIndicatorCount > 0)
		m_farmer->m_attackIndicatorCount--;
	m_farmer->m_isCommonAttackIndicatorArea = (m_farmer->m_attackIndicatorCount > 0);

	//if (m_farmer->m_isCommonAttackIndicatorArea)
	//{
	//	m_farmer->ChangeState(Farmer::FarmerState::Attack);
	//}
	//else if (m_farmer->m_isAlreadyExitAttackZone && !m_farmer->m_isAlreadyExitChaseZone)
	//{
	//	m_farmer->ChangeState(Farmer::FarmerState::Chase);
	//}
	//else
	//{
	//	//m_farmer->ChangeState(Farmer::FarmerState::Patrol);
	//}
}

void AttackIndicatorZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() != "Player") return;

	m_isPlayerInside = true;
	m_farmer->m_attackIndicatorCount++;
	m_farmer->m_isCommonAttackIndicatorArea = (m_farmer->m_attackIndicatorCount > 0);
}

void AttackIndicatorZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() != "Player") return;
	m_isPlayerInside = false;
	if (m_farmer->m_attackIndicatorCount > 0) {
		m_farmer->m_attackIndicatorCount--;
	}
	m_farmer->m_isCommonAttackIndicatorArea = (m_farmer->m_attackIndicatorCount > 0);

	if (!m_farmer->m_isCommonAttackIndicatorArea && !m_farmer->m_isAlreadyExitAttackZone)
	{
		m_farmer->ChangeState(Farmer::FarmerState::Attack);
	}
	
	else if (!m_farmer->m_isCommonAttackIndicatorArea && m_farmer->m_isAlreadyExitAttackZone && !m_farmer->m_isAlreadyExitChaseZone) {
		m_farmer->ChangeState(Farmer::FarmerState::Chase);
	}

	else if(!m_farmer->m_isCommonAttackIndicatorArea && m_farmer->m_isAlreadyExitAttackZone){
		m_farmer->ChangeState(Farmer::FarmerState::Patrol);
	}

}

