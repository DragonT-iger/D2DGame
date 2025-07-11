#pragma once
class CircleCollider : public Collider
{
public:
	void SetRadius(float newRadius) { radius = newRadius; }
	float GetRadius() const { return radius; }

	bool IsCollide(const Collider* other) const override;

private:
	float radius = 1.0f;
};

