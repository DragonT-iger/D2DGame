#include "pch.h"
#include "CreditQuit.h"

void CreditQuitButton::Awake()
{
	m_button = GetComponent<Button>();
	m_start = GameObject::Find("startBtn")->GetComponent<Button>();
	m_setting = GameObject::Find("settingBtn")->GetComponent<Button>();
	m_quit = GameObject::Find("quitBtn")->GetComponent<Button>();
	m_credit = GameObject::Find("creditBtn")->GetComponent<Button>();
	m_creditImg = GameObject::Find("credit");
	m_button->GetOwner()->SetActive(false);
}

void CreditQuitButton::Start()
{
	m_button->AddEvent([this]() {
		m_start->SetActive(true);
		m_setting->SetActive(true);
		m_credit->SetActive(true);
		m_quit->SetActive(true);
		m_button->GetOwner()->SetActive(false);
		m_creditImg->SetActive(false);
		SoundManager::Instance().UI_Shot("2.mp3");
		}, ButtonEvent::Pressed);
	m_button->AddEvent([this]() { m_button->SetSize({ 370, 255 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 370, 255 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}
