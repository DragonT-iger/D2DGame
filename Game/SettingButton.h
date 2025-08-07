#pragma once

struct Volumes {
	float bgm;
	float sfx;
	float ui;
};

class SettingButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start()	 override;

	void SetVolume(const Volumes& volumes);

private:
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

	Button* m_startBtn;
	Button* m_button;
};
