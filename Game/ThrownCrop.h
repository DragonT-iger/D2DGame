#pragma once

class ThrownCrop : public MonoBehaviour
{
public:
    void Awake() override;
    void Update(float dt) override;

    void SetVelocity(const Vector2& velocity);

private:
    Transform* m_transform = nullptr;
    Vector2 m_velocity;
    float m_gravity = -980.f;
    float m_lifeTime = 1.5f;
    float m_elapsed = 0.f;
};