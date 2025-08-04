#pragma once

class StartButton : public MonoBehaviour
{
	void Awake() override;

	void Start() override;

private:
	Button* m_button;
};
