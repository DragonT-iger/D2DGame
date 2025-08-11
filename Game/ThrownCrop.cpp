#include "pch.h"
#include "ThrownCrop.h"

void ThrownCrop::Awake()
{
    m_transform = GetComponent<Transform>();
}

void ThrownCrop::Update(float deltaTime)
{
    m_velocity.y += m_gravity * deltaTime;
    if (m_transform)
    {
        m_transform->Translate(m_velocity * deltaTime);
    }
    m_elapsed += deltaTime;
    if (m_elapsed >= m_lifeTime)
    {
        Destroy(GetOwner());
    }
}

void ThrownCrop::SetVelocity(const Vector2& velocity)
{
    m_velocity = velocity;
}