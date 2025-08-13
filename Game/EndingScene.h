#pragma once
class EndingScene :public Scene
{
	void Awake() override;
	//void Start() override;

private:
	GameObject* m_restart;
	GameObject* m_endingNum;
};

