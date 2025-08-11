#include "pch.h"
#include "QuitSetting.h"
#include "SettingButton.h"

void SettingButton::Awake()
{
	m_button = GetComponent<Button>();
	m_button->SetSize({ 305, 133 });
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
	
	if(GameObject::Find("startBtn"))
		m_startBtn = GameObject::Find("startBtn")->GetComponent<Button>();
	if(GameObject::Find("TitleBtn"))
		m_titleBtn = GameObject::Find("TitleBtn")->GetComponent<Button>();
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

		m_bgmSlider->GetComponent<Slide_Bar>()->UpdateWidthRatio(SoundManager::Instance().GetVolume_BGM());
		m_sfxSlider->GetComponent<Slide_Bar>()->UpdateWidthRatio(SoundManager::Instance().GetVolume_SFX());
		m_uiSlider->GetComponent<Slide_Bar>()->UpdateWidthRatio(SoundManager::Instance().GetVolume_UI());

		m_button->SetActive(false);
		if(m_startBtn)
			m_startBtn->SetActive(false);
		if (m_titleBtn)
			m_titleBtn->SetActive(false);
		SoundManager::Instance().UI_Shot("2.mp3");
		}, ButtonEvent::Pressed);

	m_button->AddEvent([this]() { m_button->SetSize({ 305, 133 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 331, 147 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}

void SettingButton::SetOff()
{
	if (m_cancleBtn)
	{
		m_cancleBtn->GetComponent<QuitSettingBtn>()->QuitSetting();
	}
}
