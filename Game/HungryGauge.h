#pragma once

class Player;

class HungryGauge : public MonoBehaviour
{
	void Awake() override;
	void Update(float deltaTime) override;
private:
	Player*		m_player;
	Slide_Bar* m_gauge;
};