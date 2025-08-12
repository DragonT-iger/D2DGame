#include "pch.h"
#include "Player.h"
#include "PlayerSound.h"

void PlayerSound::Awake()
{
	m_player = GetComponent<Player>();

	//필요한 사운드 벡터에 넣기
	m_walkSounds.push_back("1.mp3");
	m_walkSounds.push_back("2.mp3");
	m_walkSounds.push_back("3.mp3");
	m_walkSounds.push_back("4.mp3");
	m_walkSounds.push_back("5.mp3");

	SoundManager::Instance().GetCoreSystem()->createChannelGroup("walk", &m_walkGroup);
	SoundManager::Instance().AddSFXGroup(m_walkGroup);

	SoundManager::Instance().GetCoreSystem()->createChannelGroup("throw", &m_throwItemGroup);
	SoundManager::Instance().AddSFXGroup(m_throwItemGroup);
}

void PlayerSound::Start()
{
}

void PlayerSound::PlayWalk()
{
	if (m_walkGroup)
	{
		bool isPlaying;
		FMOD_RESULT result = m_walkGroup->isPlaying(&isPlaying);
		if (result != FMOD_OK || isPlaying)
		{
			if (result != FMOD_OK)
			{
				std::cerr << "FMOD 터짐" << isPlaying << std::endl;
			}
			return;
		}
	}

	size_t index = Random::Instance().Range(0, 4);
	//std::cout << "랜덤 재생 : " << index << std::endl;
	SoundManager::Instance().SFX_Shot(m_walkSounds[index], m_walkGroup);
}

void PlayerSound::DropCrop()
{
	SoundManager::Instance().SFX_Shot("10.mp3", m_throwItemGroup);
}

void PlayerSound::GetCrop()
{
	SoundManager::Instance().SFX_Shot("9.mp3");
}

void PlayerSound::AlreadyMaxSlot()
{
	SoundManager::Instance().SFX_Shot("22.mp3");
}

void PlayerSound::PlayHit()
{
	SoundManager::Instance().SFX_Shot("6.mp3");
}

void PlayerSound::PlayHide()
{
	SoundManager::Instance().SFX_Shot("7.mp3");
}

void PlayerSound::PlayDead()
{
	SoundManager::Instance().SFX_Shot("8.mp3");
}

void PlayerSound::PlaySubmission()
{
	SoundManager::Instance().SFX_Shot("19.mp3");
}

void PlayerSound::PlayHungry30()
{
	SoundManager::Instance().SFX_Shot("20.mp3");
}
