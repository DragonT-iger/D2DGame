#include "pch.h"
#include "AcceptSetting.h"
#include "SettingButton.h"

void AcceptSettingBtn::Awake()
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
	m_checkBtn = GameObject::Find("checkBtn");
	m_cancleBtn = GameObject::Find("cancleBtn");

	m_settingbutton = GameObject::Find("settingBtn")->GetComponent<Button>();
	if (GameObject::Find("startBtn"))
		m_startBtn = GameObject::Find("startBtn")->GetComponent<Button>();
}

void AcceptSettingBtn::Start()
{
	m_button->AddEvent([this]() {
		m_settingWnd->SetActive(false);
		m_settingText->SetActive(false);
		m_bgmText->SetActive(false);
		m_bgmSlider->SetActive(false);
		m_sfxText->SetActive(false);
		m_sfxSlider->SetActive(false);
		m_uiText->SetActive(false);
		m_uiSlider->SetActive(false);
		m_cancleBtn->SetActive(false);
		m_checkBtn->SetActive(false);

		m_settingbutton->SetActive(true);
		if(m_startBtn)
			m_startBtn->SetActive(true);

		float bgm = m_bgmSlider->GetComponent<Slide_Bar>()->GetValue();
		float sfx = m_sfxSlider->GetComponent<Slide_Bar>()->GetValue();
		float ui = m_uiSlider->GetComponent<Slide_Bar>()->GetValue();

		SoundManager::Instance().SetVolume_BGM(bgm);
		SoundManager::Instance().SetVolume_SFX(sfx);
		SoundManager::Instance().SetVolume_UI(ui);
		}, ButtonEvent::Pressed);
}
