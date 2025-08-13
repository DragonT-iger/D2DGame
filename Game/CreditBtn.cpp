#include "pch.h"
#include "CreditBtn.h"

void CreditButton::Awake()
{
	m_button = GetComponent<Button>();
	m_start = GameObject::Find("startBtn")->GetComponent<Button>();
	m_setting = GameObject::Find("settingBtn")->GetComponent<Button>();
	m_quit = GameObject::Find("quitBtn")->GetComponent<Button>();
	m_credit = GameObject::Find("credit");
	m_credit->GetComponent<Transform>()->SetPosition({ 960, 540 });
	m_credit->SetActive(false);
}

void CreditButton::Start()
{
	m_button->AddEvent([this]() { 
		if (!m_credit->IsActive()) m_credit->SetActive(true);
		m_start->SetActive(false);
		m_setting->SetActive(false);
		m_button->SetActive(false);
		m_quit->SetActive(false);
		SoundManager::Instance().UI_Shot("2.mp3"); 
		}, ButtonEvent::Pressed);
	m_button->AddEvent([this]() { m_button->SetSize({ 309, 128 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 341, 140 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}

void CreditButton::Update(float deltaTime)
{
	if (Input.GetKeyPressed(Keycode::ESCAPE) && m_credit->IsActive())
	{
		m_credit->SetActive(false);
		m_start->SetActive(true);
		m_setting->SetActive(true);
		m_button->SetActive(true);
		m_quit->SetActive(true);
	}
}
