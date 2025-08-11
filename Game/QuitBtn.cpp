#include "pch.h"
#include "QuitBtn.h"

void QuitButton::Awake()
{
	m_button = GetComponent<Button>();
}

void QuitButton::Start()
{
	m_button->AddEvent([]() { SoundManager::Instance().UI_Shot("2.mp3"); }, ButtonEvent::Pressed);
	m_button->AddEvent([this]() { m_button->SetSize({ 295, 135 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 305, 136 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}
