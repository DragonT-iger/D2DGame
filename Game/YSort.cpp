#include "pch.h"
#include "YSort.h"

void YSort::Awake()
{
    m_sprite = GetComponent<SpriteRenderer>();
    m_transform = GetComponent<Transform>();
}

void YSort::Start()
{
    Apply();
}

void YSort::Update(float deltaTime)
{
    if (!m_isStatic)
    {
        Apply();
    }
}

void YSort::Apply()
{
    if (m_sprite && m_transform)
    {
        m_sprite->SetOrderInLayer(static_cast<int>(-m_transform->GetPosition().y) + m_offset);
    }
}