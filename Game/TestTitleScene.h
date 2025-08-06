#pragma once

class TitleScene : public Scene {
public:
	void Awake() override;

	void Start() override;

private:
	GameObject* m_startButton;
	GameObject* m_Title;

	GameObject* m_slidebar;
};
