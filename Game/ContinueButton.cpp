#include "pch.h"
#include "SettingBtn_Ingame.h"
#include "ContinueButton.h"

void ContinueButton::Awake()
{
	m_button = GetComponent<Button>();
	m_EscBG = GameObject::Find("EscBG");
	m_EscBlurBG = GameObject::Find("EscBlurBG");
	m_ContinueBtn = GameObject::Find("ContinueBtn");
	m_TitleBtn = GameObject::Find("TitleBtn");
	m_SettingBtn = GameObject::Find("settingBtn");

	m_button->AddEvent([this]() { m_button->SetSize({ 280, 80 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 280, 80 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
	m_button->AddEvent([this]() {
		m_EscBG->SetActive(false);
		m_EscBlurBG->SetActive(false);
		m_ContinueBtn->SetActive(false);
		m_TitleBtn->SetActive(false);
		m_SettingBtn->GetComponent<SettingButton_Ingame>()->SetOff();
		m_SettingBtn->SetActive(false);
		SoundManager::Instance().UI_Shot("2.mp3");
		}, ButtonEvent::Pressed);
}

void ContinueButton::Start()
{
}
