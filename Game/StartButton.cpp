#include "pch.h"
#include "StartButton.h"
#include "MainScene.h"
#include "ClientSceneManager.h"

void StartButton::Awake()
{
	
}

void StartButton::Start()
{
	m_button = GetComponent<Button>();
	m_button->SetSize({ 373, 169 });

	m_button->AddEvent([]() {ClientSceneManager::Instance().LoadScene(std::make_unique<MainScene>()); SoundManager::Instance().UI_Shot("2.mp3"); }, ButtonEvent::Pressed);
	m_button->AddEvent([this]() { m_button->SetSize({ 373, 169 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() { 
		m_button->SetSize({ 399, 181 }); 
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}
