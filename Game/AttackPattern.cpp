#include "pch.h"
#include "AttackPattern.h"
#include "AttackEffect.h"
#include "SpriteRenderer.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "FarmerZone.h"

void AttackPattern::SetOffsets(const std::vector<Vector2>& offsets)
{
    m_offsets = offsets;
}

void AttackPattern::CreateIndicators(Farmer* owner, const Vector2& origin, float radius)
{
    for (const auto& offset : m_offsets)
    {
        GameObject* indicator = Instantiate("AttackIndicator");
        if (!indicator) continue;

        auto indicatorTransform = indicator->GetComponent<Transform>();
        if (indicatorTransform)
            indicatorTransform->SetPosition(origin + offset);

        auto sr = indicator->AddComponent<SpriteRenderer>();
        if (sr)
        {
            sr->SetOpacity(0.5f);
            sr->SetBitmap(ResourceManager::Instance().LoadTexture("redCircle.png"));
        }

        indicator->AddComponent<CircleCollider>();

        indicator->GetComponent<Transform>()->SetScale(m_effectScale);
        auto zone = indicator->AddComponent<AttackIndicatorZone>();
        if (zone)
            zone->Initialize(owner);

        m_indicators.push_back(indicator);
    }
}
void AttackPattern::ClearIndicators()
{

    for (auto* indicator : m_indicators)
    {
        Destroy(indicator);
    }
    m_indicators.clear();
}

void AttackPattern::Execute(const Vector2& origin, float radius)
{
    if (!m_indicators.empty())
    {
        for (auto* indicator : m_indicators)
        {
            Vector2 pos = indicator->GetComponent<Transform>()->GetPosition();
            GameObject* effect = Instantiate("AttackEffect");
            effect->GetComponent<Transform>()->SetScale(m_effectScale);
            if (!effect) continue;
            auto effTransform = effect->GetComponent<Transform>();
            if (effTransform)
                effTransform->SetPosition(pos);
            effect->AddComponent<SpriteRenderer>();
            auto collider = effect->AddComponent<CircleCollider>();
            if (collider)
                collider->SetRadius(radius);
            effect->AddComponent<AttackEffect>();

            Destroy(indicator);
        }
        m_indicators.clear();
    }
    else
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
}