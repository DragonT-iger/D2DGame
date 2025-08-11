#pragma once

class TitleScene : public Scene {
public:
	void Awake() override;

	void Start() override;

private:
	GameObject* m_startButton;
	GameObject* m_settingButton;
	GameObject* m_creditButton;
	GameObject* m_quitButton;

	GameObject* m_Title;

	GameObject* m_settingWnd;
	GameObject* m_settingText;
	GameObject* m_bgmText;
	GameObject* m_bgmSlider;
	GameObject* m_sfxText;
	GameObject* m_sfxSlider;
	GameObject* m_uiText;
	GameObject* m_uiSlider;
	GameObject* m_cancleBtn;
	GameObject* m_checkBtn;
};
