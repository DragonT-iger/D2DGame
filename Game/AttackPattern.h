#pragma once

class Farmer;

class AttackPattern : public MonoBehaviour
{
public:
    void SetOffsets(const std::vector<Vector2>& offsets);
    void CreateIndicators(Farmer* owner, const Vector2& origin, float radius);
    void ClearIndicators();
    bool HasIndicators() const { return !m_indicators.empty(); }
    void Execute(const Vector2& origin, float radius);

private:
    std::vector<Vector2> m_offsets;
    std::vector<GameObject*> m_indicators;
};