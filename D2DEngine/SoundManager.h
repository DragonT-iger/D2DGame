#pragma once
//


class SoundManager
{
public:
	bool Init();
	void Update();
	void Shutdown();

	void PlayOneShot(const std::string& eventPath);
	void SetVolume(float volume);

private:
	FMOD::Studio::System* m_studioSystem = nullptr;
	FMOD::System* m_coreSystem = nullptr;

	float m_volume = 1.0f;
};
