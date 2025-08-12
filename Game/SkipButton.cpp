#include "pch.h"
#include "MainScene.h"
#include "ClientSceneManager.h"
#include "SkipButton.h"

void SkipButton::Awake()
{

}

void SkipButton::Start()
{
	m_button = GetComponent<Button>();
	m_button->SetSize({ 250, 100 });

	m_button->AddEvent([]() {ClientSceneManager::Instance().LoadScene(std::make_unique<MainScene>()); SoundManager::Instance().UI_Shot("2.mp3"); }, ButtonEvent::Pressed);
	m_button->AddEvent([this]() { m_button->SetSize({ 250, 100 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 270, 110 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
}
