#include "pch.h"
#include "Player.h"
#include "PlayerSound.h"

void PlayerSound::Awake()
{
	m_player = GetComponent<Player>();

	//ÇÊ¿äÇÑ »ç¿îµå º¤ÅÍ¿¡ ³Ö±â
	m_walkSounds.push_back("1.mp3");
	m_walkSounds.push_back("2.mp3");
	m_walkSounds.push_back("3.mp3");
	m_walkSounds.push_back("4.mp3");
	m_walkSounds.push_back("5.mp3");

	SoundManager::Instance().GetCoreSystem()->createChannelGroup("walk", &m_walkGroup);
	SoundManager::Instance().AddSFXGroup(m_walkGroup);

	SoundManager::Instance().GetCoreSystem()->createChannelGroup("throw", &m_throwItemGroup);
	SoundManager::Instance().AddSFXGroup(m_throwItemGroup);

	SoundManager::Instance().GetCoreSystem()->createChannelGroup("gameover", &m_GameOverGroup);
	SoundManager::Instance().AddSFXGroup(m_GameOverGroup);
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
				std::cerr << "FMOD ÅÍÁü" << isPlaying << std::endl;
			}
			return;
		}
	}

	size_t index = Random::Instance().Range(0, 4);
	//std::cout << "·£´ý Àç»ý : " << index << std::endl;
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

bool PlayerSound::PlayGameOver()
{
	static bool alreadyPlaying = false;

	if (m_GameOverGroup)
	{
		bool isPlaying = false;
		FMOD_RESULT result = m_GameOverGroup->isPlaying(&isPlaying);
		if (result != FMOD_OK || isPlaying)
		{
			if (result != FMOD_OK)
			{
				std::cerr << "FMOD ÅÍÁü" << isPlaying << std::endl;
			}
			return isPlaying;
		}
		else
		{
			if (!alreadyPlaying)
			{
				SoundManager::Instance().SFX_Shot("23.mp3", m_GameOverGroup);
				alreadyPlaying = true;
			}
			return false;
		}
	}
}

bool PlayerSound::PlayClear()
{
	static bool alreadyPlaying = false;

	if (m_GameOverGroup)
	{
		bool isPlaying = false;
		FMOD_RESULT result = m_GameOverGroup->isPlaying(&isPlaying);
		if (result != FMOD_OK || isPlaying)
		{
			if (result != FMOD_OK)
			{
				std::cerr << "FMOD ÅÍÁü" << isPlaying << std::endl;
			}
			return isPlaying;
		}
		else
		{
			if (!alreadyPlaying)
			{
				SoundManager::Instance().SFX_Shot("24.mp3", m_GameOverGroup);
				alreadyPlaying = true;
			}
			return false;
		}
	}
}
