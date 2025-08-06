#pragma once

class Player;

class PlayerSound : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

	void PlaySound();

	void PlayWalk();

private:
	Player*												m_player;
	std::vector<std::string>		m_walkSounds;
	FMOD::Channel*	m_walkChannel = nullptr;

	std::vector<FMOD::Channel*>	m_sfxChannels;
};
