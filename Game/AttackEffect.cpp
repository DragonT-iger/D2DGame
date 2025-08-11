#include "pch.h"
#include "AttackEffect.h"
#include "Animator.h"
#include "ResourceManager.h"
#include "Random.h"
#include "GameObject.h"

FMOD::ChannelGroup* AttackEffect::m_effectSoundGroup = nullptr;

void AttackEffect::Awake()
{
    m_animator = GetOwner()->AddComponent<Animator>();

    if (!AttackEffect::GetChannelGroup())
    {
        SoundManager::Instance().GetCoreSystem()->createChannelGroup("shot", &AttackEffect::GetChannelGroup());
        SoundManager::Instance().AddSFXGroup(AttackEffect::GetChannelGroup());
    }
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
    if (m_animator)
    {
        if (m_elapsedTime >= m_soundTime)
        {
            bool isPlaying = false;
            AttackEffect::GetChannelGroup()->isPlaying(&isPlaying);
            if(!isPlaying)
                SoundManager::Instance().SFX_Shot("18.mp3", AttackEffect::GetChannelGroup());
            m_elapsedTime = 0.0f;
        }
        else
        {
            m_elapsedTime += deltaTime;
        }
        if(m_animator->IsAnimeEnd())
            Destroy(GetOwner());
    }
}