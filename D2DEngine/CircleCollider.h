#pragma once

class CircleCollider : public Collider
{
public:

	void SetRadius(float newRadius) { m_radius = newRadius; }
	float GetRadius() const { return m_radius; }

	bool IsCollide(const Collider* other) const override;

	//디버그용
	void DrawCollider() override;

	ColliderInfo GetColliderInfo() override;

private:
	float m_radius = 1.0f; // 상대적 크기 아님
};

