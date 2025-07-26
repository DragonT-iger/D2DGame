#include "pch.h"
#include "SoundManager.h"

bool SoundManager::Init()
{
	FMOD::System* SoundManager = nullptr;

	FMOD_CHECK(FMOD::System_Create(&SoundManager));
}

void SoundManager::Update()
{

}

void SoundManager::Shutdown()
{

}

void SoundManager::PlayOneShot(const std::string& eventPath)
{

}

void SoundManager::SetVolume(float volume)
{

}
