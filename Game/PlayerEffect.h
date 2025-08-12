#pragma once

class PlayerEffect : public MonoBehaviour
{
public:
	void Awake() override;
	void Update(float deltaTime) override;

	void HitEffect();

	void SubMissonEffect();

private:
	GameObject* m_player;
	Transform* m_transform;
	Animator* m_animator;
};