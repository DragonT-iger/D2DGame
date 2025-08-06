#pragma once

class GameManager : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

private:
	GameObject* m_player;

};
