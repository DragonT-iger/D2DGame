#pragma once
class SafeZone : public MonoBehaviour
{


public:
	SafeZone(float x, float y) : m_x(x), m_y(y) {}

	void Awake() override;




private:
	float m_x = 0;
	float m_y = 0;


	SpriteRenderer* m_spriteRenderer = nullptr;
};

