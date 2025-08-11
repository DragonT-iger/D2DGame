#pragma once

class QuitButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;

private:
	Button* m_button;
};
