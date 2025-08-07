#include "pch.h"
#include "SettingButton.h"

void SettingButton::Awake()
{
	m_button = GetComponent<Button>();
	m_settingWnd = GameObject::Find("settingWnd");
	m_settingText = GameObject::Find("settingText");
	m_bgmText = GameObject::Find("bgmText");
	m_bgmSlider = GameObject::Find("bgmSlider");
	m_sfxText = GameObject::Find("sfxText");
	m_sfxSlider = GameObject::Find("sfxSlider");
	m_uiText = GameObject::Find("uiText");
	m_uiSlider = GameObject::Find("uiSlider");
	m_cancleBtn = GameObject::Find("cancleBtn");
	m_checkBtn = GameObject::Find("checkBtn");

	m_startBtn = GameObject::Find("startBtn")->GetComponent<Button>();
}

void SettingButton::Start()
{
	m_button->AddEvent([this]() {
		m_settingWnd->SetActive(true);
		m_settingText->SetActive(true);
		m_bgmText->SetActive(true);
		m_bgmSlider->SetActive(true);
		m_sfxText->SetActive(true);
		m_sfxSlider->SetActive(true);
		m_uiText->SetActive(true);
		m_uiSlider->SetActive(true);
		m_cancleBtn->SetActive(true);
		m_checkBtn->SetActive(true);

		m_bgmSlider->GetComponent<Slide_Bar>()->UpdateWidthRatio(curBgm_Volume);
		m_sfxSlider->GetComponent<Slide_Bar>()->UpdateWidthRatio(curSfx_Volume);
		m_uiSlider->GetComponent<Slide_Bar>()->UpdateWidthRatio(curUI_Volume);

		m_button->SetActive(false);
		m_startBtn->SetActive(false);
		}, ButtonEvent::Pressed);
}

void SettingButton::SetVolume(const Volumes& volumes)
{
	curBgm_Volume = volumes.bgm;
	curSfx_Volume = volumes.sfx;
	curUI_Volume = volumes.ui;
}
