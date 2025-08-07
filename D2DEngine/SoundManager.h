#pragma once

class SoundManager
{
public:
	static SoundManager& Instance();

	bool Init();
	void Update();
	void Shutdown();

	void AddBGMGroup(FMOD::ChannelGroup* ChannelGroup);
	void AddSFXGroup(FMOD::ChannelGroup* ChannelGroup);
	void AddUIGroup(FMOD::ChannelGroup* ChannelGroup);

	void BGM_Shot(const std::string& fileName, FMOD::ChannelGroup* ChannelGroup = nullptr);
	void SFX_Shot(const std::string& fileName, FMOD::ChannelGroup* ChannelGroup = nullptr);
	void UI_Shot(const std::string& fileName, FMOD::ChannelGroup* ChannelGroup = nullptr);

	void SetVolume_Main(float volume); //other volume = mainV * otherV;
	void SetVolume_BGM(float volume);
	void SetVolume_SFX(float volume);
	void SetVolume_UI(float volume);

	float GetVolume_Main() { return m_Volume_Main; }
	float GetVolume_BGM() { return m_Volume_BGM; }
	float GetVolume_SFX() { return m_Volume_SFX; }
	float GetVolume_UI() { return m_Volume_UI; }

	void SetDirty(); // dirty = true;

	void ConvertBGMSource(const std::unordered_map<std::string, std::filesystem::path>& container);
	void ConvertSFXSource(const std::unordered_map<std::string, std::filesystem::path>& container);
	void ConvertUISource(const std::unordered_map<std::string, std::filesystem::path>& container);

	FMOD::System* GetCoreSystem() { return m_coreSystem; }

private:
	SoundManager()                                = default;
	~SoundManager();
	SoundManager            (const SoundManager&) = delete;
	SoundManager& operator= (const SoundManager&) = delete;
	SoundManager            (SoundManager&&)      = delete;
	SoundManager& operator= (SoundManager&&)      = delete;

	//FMOD::Studio::System* m_studioSystem = nullptr;
	FMOD::System* m_coreSystem = nullptr;

	std::unordered_map<std::string, FMOD::Sound*> L_BGM;
	std::unordered_map<std::string, FMOD::Sound*> L_SFX;
	std::unordered_map<std::string, FMOD::Sound*> L_UI;

	FMOD::ChannelGroup* m_mainGroup = nullptr;
	FMOD::ChannelGroup* m_bgmGroup = nullptr;
	FMOD::ChannelGroup* m_sfxGroup = nullptr;
	FMOD::ChannelGroup* m_uiGroup = nullptr;

	float m_Volume_Main = 1.0f;
	float m_Volume_BGM  = 1.0f;
	float m_Volume_SFX  = 1.0f;
	float m_Volume_UI   = 1.0f;

	bool m_SoundDirty = false;
	bool m_Dirty_BGM   = false;
	bool m_Dirty_SFX = false;
	bool m_Dirty_UI = false;

};