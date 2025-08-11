#pragma once

class Animator;

class AttackEffect : public MonoBehaviour
{
public:
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;

	static FMOD::ChannelGroup*& GetChannelGroup() { return m_effectSoundGroup; }

private:
    Animator* m_animator = nullptr;

    static FMOD::ChannelGroup* m_effectSoundGroup;

    float m_soundTime = 0.3f;
	float m_elapsedTime = 0.0f;
};