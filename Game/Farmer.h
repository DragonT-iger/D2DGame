#pragma once
class Farmer : public MonoBehaviour
{
	void Awake() override;

	void Start() override;
	
	void Update(float deltaTime) override;

    void PickRandomDirection();

	//애니메이션

	//AI


private:
    enum class State
    {
        Idle,
        Run,
        Attack
    };

    Animator* m_animator = nullptr;
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
    BoxCollider* m_boxCollider = nullptr;

    State   m_state = State::Idle;
    Vector2 m_direction = Vector2::zero;
    float   m_speed = 100.f;
    float   m_dirTimer = 0.f;
    float   m_dirInterval = 2.f;
};

