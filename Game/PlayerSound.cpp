#include "pch.h"
#include "Player.h"
#include "PlayerSound.h"

void PlayerSound::Awake()
{
	m_player = GetComponent<Player>();

	//필요한 사운드 벡터에 넣기
	m_walkSounds.push_back("farmer_Footstep1.mp3");
	m_walkSounds.push_back("farmer_Footstep2.mp3");
	m_walkSounds.push_back("farmer_Footstep3.mp3");
	m_walkSounds.push_back("farmer_Footstep4.mp3");
	m_walkSounds.push_back("farmer_Footstep5.mp3");

	m_walkChannel = nullptr;
}

void PlayerSound::Start()
{
}

void PlayerSound::Update(float deltaTime)
{
	PlaySound();
}

void PlayerSound::PlaySound()
{
	switch (m_player->action)
	{
	case Action::Idle:
		break;
	case Action::Walk:
		PlayWalk();
		break;
	case Action::Hit:
		break;
	case Action::Steal:
		break;
	}
}

void PlayerSound::PlayWalk()
{
	if (m_walkChannel)
	{
		bool isPlaying;
		FMOD_RESULT result = m_walkChannel->isPlaying(&isPlaying);
		if (result != FMOD_OK || isPlaying)
		{
			if(result != FMOD_OK)
				std::cerr << "FMOD 터짐" << isPlaying << std::endl;
			return;
		}
		else
		{
			m_walkChannel = nullptr;
		}
	}

	size_t index = Random::Instance().Range(0, 4);
	std::cout << "랜덤 재생 : " << index << std::endl;
	SoundManager::Instance().SFX_Shot(m_walkSounds[index], &m_walkChannel);
}
