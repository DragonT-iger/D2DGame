#pragma once
class EndSceneManager : public MonoBehaviour
{
	void Awake() override;
	void Start() override;



public:
	SpriteRenderer* m_spriteRenderer = nullptr;
	Animator* m_animator = nullptr;
};

