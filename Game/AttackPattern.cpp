#include "pch.h"
#include "AttackPattern.h"
#include "AttackEffect.h"
#include "SpriteRenderer.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"

void AttackPattern::SetOffsets(const std::vector<Vector2>& offsets)
{
    m_offsets = offsets;
}

void AttackPattern::Execute(const Vector2& origin, float radius)
{
    for (const auto& offset : m_offsets)
    {
        GameObject* effect = Instantiate("AttackEffect");
        if (!effect) continue;
        auto effTransform = effect->GetComponent<Transform>();
        if (effTransform)
            effTransform->SetPosition(origin + offset);
        effect->AddComponent<SpriteRenderer>();
        auto collider = effect->AddComponent<CircleCollider>();
        if (collider)
            collider->SetRadius(radius);
        effect->AddComponent<AttackEffect>();
    }
}
