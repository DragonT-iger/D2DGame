#pragma once

class AttackPattern
{
public:
    void SetOffsets(const std::vector<Vector2>& offsets);
    void Execute(const Vector2& origin, float radius);

private:
    std::vector<Vector2> m_offsets;
};