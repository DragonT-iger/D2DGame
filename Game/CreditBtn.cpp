#include "pch.h"
#include "CreditBtn.h"

void CreditButton::Awake()
{
	m_button = GetComponent<Button>();
}

void CreditButton::Start()
{
	m_button->AddEvent([]() {SoundManager::Instance().UI_Shot("2.mp3"); }, ButtonEvent::Pressed);
	m_button->AddEvent([this]() { m_button->SetSize({ 309, 128 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 341, 140 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}
