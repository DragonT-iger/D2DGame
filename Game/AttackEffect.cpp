#include "pch.h"
#include "AttackEffect.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Random.h"
#include "GameObject.h"

void AttackEffect::Awake()
{
    m_animator = GetOwner()->AddComponent<Animator>();
}

void AttackEffect::Start()
{
    auto fire1 = ResourceManager::Instance().LoadAnimationClip("Bullet.json", "fire1");
    auto fire2 = ResourceManager::Instance().LoadAnimationClip("Bullet.json", "fire2");
    if (fire1) m_animator->AddClip("fire1", fire1, false);
    if (fire2) m_animator->AddClip("fire2", fire2, false);
    int idx = Random::Instance().Range(0, 2);
    m_animator->ChangeState(idx == 0 ? "fire1" : "fire2");
}

void AttackEffect::Update(float deltaTime)
{
    if (m_animator && m_animator->IsAnimeEnd())
    {
        Destroy(GetOwner());
    }
}