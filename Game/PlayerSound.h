#pragma once

class Player;
enum class Action;

class PlayerSound : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;

	void PlayWalk();

	void DropCrop();
	void GetCrop();

	void AlreadyMaxSlot();

	void PlayHit();

	void PlayHide();

	void PlayDead();

private:
	Player*												m_player;
	std::vector<std::string>		m_walkSounds;
	FMOD::ChannelGroup* m_walkGroup = nullptr;
	FMOD::ChannelGroup* m_throwItemGroup = nullptr;

	float m_throwTime = 0.1f;
	float m_throwelapsedTime = 0.0f;
};
