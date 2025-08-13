#include "pch.h"
#include "FarmerZone.h"
#include "Farmer.h"
#include "Player.h"
#include "GameManager.h"

FMOD::ChannelGroup* FarmerZone::m_farmerBgmGroup = nullptr;
FMOD::ChannelGroup* FarmerZone::m_WarningBgmGroup = nullptr;

void FarmerZone::Awake()
{
	GetOwner()->AddComponent<CircleCollider>()->SetRadius(m_circleColliderRadius);
	if (!m_farmerBgmGroup)
	{
		SoundManager::Instance().GetCoreSystem()->createChannelGroup("farmerbgm", &m_farmerBgmGroup);
		SoundManager::Instance().AddBGMGroup(m_farmerBgmGroup);
	}
}

void ChaseZone::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
	{
		m_farmer->m_isAlreadyExitChaseZone = false;
		m_farmer->PlayChaseZoneSound();
	}
}

void ChaseZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
	{
		m_farmer->m_isAlreadyExitChaseZone = true; 
		m_farmer->StopSound();
		bool isPlaying = false;
		m_farmerBgmGroup->isPlaying(&isPlaying);
		if(isPlaying && !SoundManager::Instance().BGM_IsPlaying())
			SoundManager::Instance().BGM_Shot("2.mp3");
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

void AttackZone::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {

		if (other->GetOwner()->GetComponent<Player>()->GetVisible() == Visibilty::Hide) {

			m_farmer->ChangeState(Farmer::FarmerState::Patrol);
			return;
		}
		if (Farmer::FarmerState::Attack != m_farmer->GetFarmerState()) {
			m_farmer->ChangeState(Farmer::FarmerState::Attack);
		}
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
		m_farmer->m_isAlreadyExitAlertZone = false;
	}
}

void AlertZone::OnTriggerStay(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player")
	{
		bool isPlaying = false;
		m_farmerBgmGroup->isPlaying(&isPlaying);
		if (!isPlaying)
			SoundManager::Instance().BGM_Shot("3.mp3", m_farmerBgmGroup);
	}	
}

void AlertZone::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "Player") {

		m_farmer->m_isAlreadyExitAlertZone = true;
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

	//if (!m_farmer->m_isCommonAttackIndicatorArea && !m_farmer->m_isAlreadyExitAttackZone)
	//{
	//	m_farmer->ChangeState(Farmer::FarmerState::Attack);
	//}
	//
	//else if (!m_farmer->m_isCommonAttackIndicatorArea && m_farmer->m_isAlreadyExitAttackZone && !m_farmer->m_isAlreadyExitChaseZone) {
	//	m_farmer->ChangeState(Farmer::FarmerState::Chase);
	//}

	//else if(!m_farmer->m_isCommonAttackIndicatorArea && m_farmer->m_isAlreadyExitAttackZone){
	//	m_farmer->ChangeState(Farmer::FarmerState::Patrol);
	//}

	if (!m_farmer)
		return;

	if (m_isPlayerInside)
	{
			auto playerObj = SceneManager::Instance().GetActiveScene()->GetPlayer();
			if (playerObj)
			{
				auto player = playerObj->GetComponent<Player>();
				if (player)
				{
					if (player->GetVisible() != Visibilty::Hide)
						{
							if (player->GetHittable())
							{
								player->SetHp(player->GetHp() - 1);
								player->SetAction(Action::Hit);
							}

							/*if (player->GetHittable())
							{
								player->SetAction(Action::Hit);
							}*/
						}

				}
			}
			m_farmer->m_hasDamagedPlayer = true;

		if (m_farmer->m_attackIndicatorCount > 0)
			m_farmer->m_attackIndicatorCount--;
		m_farmer->m_isCommonAttackIndicatorArea = (m_farmer->m_attackIndicatorCount > 0);
	}
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

	//if (!m_farmer->m_isCommonAttackIndicatorArea && !m_farmer->m_isAlreadyExitAttackZone)
	//{
	//	m_farmer->ChangeState(Farmer::FarmerState::Attack);
	//}
	//
	//else if (!m_farmer->m_isCommonAttackIndicatorArea && m_farmer->m_isAlreadyExitAttackZone && !m_farmer->m_isAlreadyExitChaseZone) {
	//	m_farmer->ChangeState(Farmer::FarmerState::Chase);
	//}

	//else if(!m_farmer->m_isCommonAttackIndicatorArea && m_farmer->m_isAlreadyExitAttackZone){
	//	m_farmer->ChangeState(Farmer::FarmerState::Patrol);
	//}


	// 이거 주석 풀면 중간에 공격 풀림
}

