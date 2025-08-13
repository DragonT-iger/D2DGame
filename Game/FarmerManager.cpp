#include "pch.h"
#include "FarmerManager.h"
#include "Farmer.h"

FarmerManager::~FarmerManager()
{
    m_farmerWarningGroup->stop();
}

void FarmerManager::Awake()
{
    std::vector<Vector2> positions = {
        { -1100.f,  780.f },
        {  1100.f,  780.f },
        { -1100.f, -750.f },
        {  1100.f, -750.f }
    };


   

    m_farmers.reserve(positions.size());

    for (const auto& pos : positions)
    {
        GameObject* farmerObj = Instantiate("Farmer");
        farmerObj->AddComponent<Farmer>();
        farmerObj->GetComponent<Transform>()->SetPosition(pos);
        m_farmers.push_back(farmerObj);
    }

    SoundManager::Instance().GetCoreSystem()->createChannelGroup("warning", &m_farmerWarningGroup);
    SoundManager::Instance().AddSFXGroup(m_farmerWarningGroup);
}

void FarmerManager::PlayWarningSound()
{
	bool isPlaying = false;
    m_farmerWarningGroup->isPlaying(&isPlaying);

    if (!isPlaying)
    {
        SoundManager::Instance().SFX_Shot("21.mp3", m_farmerWarningGroup);
    }
}

void FarmerManager::WarningSoundStop()
{
    m_farmerWarningGroup->stop();
}
