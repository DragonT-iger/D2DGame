#pragma once

class ContinueButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;

private:
	Button* m_button;

	GameObject* m_EscBG;
	GameObject* m_EscBlurBG;
	GameObject* m_ContinueBtn;
	GameObject* m_TitleBtn;
	GameObject* m_SettingBtn;

	bool isActive = false;
};
