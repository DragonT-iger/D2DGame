#include "pch.h"
#include "Farmer.h"

void Farmer::Awake()
{
	GetOwner()->AddComponent<SpriteRenderer>();
	m_animator = GetOwner()->AddComponent<Animator>();
}

void Farmer::Start()
{

	auto idle = ResourceManager::Instance().LoadAnimationClip("farmertest2.json", "idle");
	auto run = ResourceManager::Instance().LoadAnimationClip("farmertest2.json", "run");
	auto attack = ResourceManager::Instance().LoadAnimationClip("farmertest2.json", "attack");

	m_animator->AddClip("idle", idle, true);
	m_animator->AddClip("run", run, true);
	m_animator->AddClip("attack", attack, false);

	m_animator->SetEntryState("idle");
	//m_animator->ChangeState("idle");

}
