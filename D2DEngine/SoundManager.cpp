#include "pch.h"
#include <filesystem>
#include "SoundManager.h"
#include "Fmod_Error.h"
//bgm, sfx, ui 별로 맵 만들고 시스템 init 

SoundManager& SoundManager::Instance()
{
	static SoundManager inst;
	return inst;
}

bool SoundManager::Init()
{
	FMOD_RESULT result = FMOD::System_Create(&m_coreSystem);
	if (result != FMOD_OK) { FMOD_LOG(result); FMOD_ASSERT(result); return false; }

	//3D Sound 추가시 수정
	result = m_coreSystem->init(64, FMOD_INIT_NORMAL, nullptr);
	if (result != FMOD_OK) { FMOD_LOG(result); FMOD_ASSERT(result); return false; }

	return true;
}

void SoundManager::Update()
{
	m_coreSystem->update();
}

void SoundManager::Shutdown()
{
	for (auto& n : L_BGM) { n.second->release(); }
	for (auto& n : L_SFX) { n.second->release(); }
	for (auto& n : L_UI)  { n.second->release(); }
	m_coreSystem->release();
}

void SoundManager::OneShot(const std::string& eventPath)
{
	//L_BGM.find(eventPath)->second->
}

void SoundManager::SetVolume(float volume) // volume: 0 ~ 1
{
	if (volume < 0){ volume = 0; }
	m_volume = volume;
}


