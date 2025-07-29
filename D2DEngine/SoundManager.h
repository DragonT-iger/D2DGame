#pragma once

class SoundManager
{
public:
	bool Init();
	void Update();
	void Shutdown();

	void OneShot(const std::string& eventPath);
	void SetVolume(float volume);

	static SoundManager& Instance();

private:
	SoundManager() = default;
	~SoundManager() = default;

	SoundManager            (const SoundManager&) = delete;
	SoundManager& operator= (const SoundManager&) = delete;

	SoundManager            (SoundManager&&) = delete;
	SoundManager& operator= (SoundManager&&) = delete;

	//FMOD::Studio::System* m_studioSystem = nullptr;
	FMOD::System* m_coreSystem = nullptr;

	std::unordered_map<std::string, FMOD::Sound*> L_BGM;
	std::unordered_map<std::string, FMOD::Sound*> L_SFX;
	std::unordered_map<std::string, FMOD::Sound*> L_UI;

	float m_volume = 1.0f;
};
