#include "pch.h"
#include "Player.h"
#include "PlayerSound.h"

void PlayerSound::Awake()
{
	m_player = GetComponent<Player>();

	//필요한 사운드 벡터에 넣기
	m_walkSounds.push_back("sample_two.wav");
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
		m_walkChannel->isPlaying(&isPlaying);

	if (!isPlaying || !m_walkChannel)
	{
		size_t index = Random::Instance().Range(0, 4);
		SoundManager::Instance().SFX_Shot(m_walkSounds[index], m_walkChannel);
	}
	
}
