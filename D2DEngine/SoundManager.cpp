#include "pch.h"
#include <filesystem>
#include "SoundManager.h"
#include "Fmod_Error.h"

constexpr int ChannelCount = 128;

SoundManager& SoundManager::Instance()
{
	static SoundManager inst;
	return inst;
}

bool SoundManager::Init()
{
	FMOD_RESULT result;
	if (!m_coreSystem)
	{
		result = FMOD::System_Create(&m_coreSystem);
		if (result != FMOD_OK) { FMOD_LOG(result); FMOD_ASSERT(result); return false; }


		//3D Sound 추가시 수정
		result = m_coreSystem->init(ChannelCount, FMOD_INIT_NORMAL, nullptr);
		if (result != FMOD_OK) { FMOD_LOG(result); FMOD_ASSERT(result); return false; }

		m_coreSystem->getMasterChannelGroup(&m_mainGroup);

		if (!m_bgmGroup) m_coreSystem->createChannelGroup("BGM", &m_bgmGroup);
		if (!m_sfxGroup) m_coreSystem->createChannelGroup("SFX", &m_sfxGroup);
		if (!m_uiGroup) m_coreSystem->createChannelGroup("UI", &m_uiGroup);

		m_mainGroup->addGroup(m_bgmGroup);
		m_mainGroup->addGroup(m_sfxGroup);
		m_mainGroup->addGroup(m_uiGroup);

		ConvertBGMSource(ResourceManager::Instance().GetBGMPaths());	//args paths
		ConvertSFXSource(ResourceManager::Instance().GetSFXPaths());	//args paths
		ConvertUISource(ResourceManager::Instance().GetUIPaths());		//args paths
	}
	return true;
}

SoundManager::~SoundManager()
{
	m_coreSystem->release();
	m_bgmGroup->release();
	m_sfxGroup->release();
	m_uiGroup->release();
	m_mainGroup->release();
}

void SoundManager::SetDirty()
{
	m_SoundDirty = true;
	m_Dirty_BGM = true;
	m_Dirty_SFX = true;
	m_Dirty_UI = true;
}

//3D 설정시 변경 //FMOD_3D
void SoundManager::ConvertBGMSource(const std::unordered_map<std::string, std::filesystem::path>& bgm)
{
	for (auto& n : bgm)
	{
		FMOD::Sound* temp;
		m_coreSystem->createSound(n.second.string().c_str(), FMOD_LOOP_NORMAL | FMOD_2D, nullptr, &temp);

		L_BGM.emplace(n.first, temp);
	}
}

void SoundManager::ConvertSFXSource(const std::unordered_map<std::string, std::filesystem::path>& sfx)
{
	for (auto& n : sfx)
	{
		FMOD::Sound* temp;
		m_coreSystem->createSound(n.second.string().c_str(), FMOD_DEFAULT | FMOD_2D, nullptr, &temp);

		L_SFX.emplace(n.first, temp);
	}
}

void SoundManager::ConvertUISource(const std::unordered_map<std::string, std::filesystem::path>& ui)
{
	for (auto& n : ui)
	{
		FMOD::Sound* temp;
		m_coreSystem->createSound(n.second.string().c_str(), FMOD_DEFAULT | FMOD_2D, nullptr, &temp);

		L_UI.emplace(n.first, temp);
	}
}



void SoundManager::Update() //매 프레임 마다 필수 호출
{
	m_coreSystem->update();
}

void SoundManager::Shutdown()
{
	for (auto& n : L_BGM) { n.second->release(); }
	for (auto& n : L_SFX) { n.second->release(); }
	for (auto& n : L_UI) { n.second->release(); }
	m_coreSystem->release();
}

void SoundManager::AddBGMGroup(FMOD::ChannelGroup* ChannelGroup)
{
	m_bgmGroup->addGroup(ChannelGroup);
}

void SoundManager::AddSFXGroup(FMOD::ChannelGroup* ChannelGroup)
{
	m_sfxGroup->addGroup(ChannelGroup);
}

void SoundManager::AddUIGroup(FMOD::ChannelGroup* ChannelGroup)
{
	m_uiGroup->addGroup(ChannelGroup);
}

void SoundManager::BGM_Shot(const std::string& fileName, FMOD::ChannelGroup* ChannelGroup)
{
	std::cout << fileName << std::endl;

	FMOD::Channel* pChannel = nullptr;

	bool isBGMPlaying = false;
	m_bgmGroup->isPlaying(&isBGMPlaying);

	if (isBGMPlaying)
	{
		m_bgmGroup->stop();
	}
	//fade in,out 만들거여?

	auto it = L_BGM.find(fileName);

	if (it != L_BGM.end())
	{
		m_coreSystem->playSound(it->second, ChannelGroup, false, &pChannel);
	}
}

void SoundManager::SFX_Shot(const std::string& fileName, FMOD::ChannelGroup* ChannelGroup)
{
	FMOD::Channel* pChannel = nullptr;

	auto it = L_SFX.find(fileName);

	if (it != L_SFX.end())
	{
		m_coreSystem->playSound(it->second, ChannelGroup, false, &pChannel);
	}
}

void SoundManager::UI_Shot(const std::string& fileName, FMOD::ChannelGroup* ChannelGroup)
{
	FMOD::Channel* pChannel = nullptr;

	auto it = L_UI.find(fileName);

	if (it != L_UI.end())
	{
		m_coreSystem->playSound(it->second, ChannelGroup, false, &pChannel);
	}
}


void SoundManager::SetVolume_Main(float volume)
{
	if (m_SoundDirty == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_Main = volume;

	m_mainGroup->setVolume(m_Volume_Main);

	m_SoundDirty = false;
}

void SoundManager::SetVolume_BGM(float volume)
{
	if (m_Dirty_BGM == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_BGM = m_Volume_Main * volume;

	m_bgmGroup->setVolume(m_Volume_BGM);

	m_Dirty_BGM = false;
}

void SoundManager::SetVolume_SFX(float volume)
{
	if (m_Dirty_SFX == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_SFX = m_Volume_Main * volume;

	m_sfxGroup->setVolume(m_Volume_SFX);

	m_Dirty_SFX = false;
}

void SoundManager::SetVolume_UI(float volume)
{
	if (m_Dirty_UI == false) return;
	if (volume < 0) { volume = 0; }
	else if (volume > 1.0f) { volume = 1.0f; }
	m_Volume_UI = m_Volume_Main * volume;

	m_uiGroup->setVolume(m_Volume_UI);

	m_Dirty_UI = false;
}

