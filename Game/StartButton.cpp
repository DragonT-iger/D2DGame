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

	m_button->AddEvent([]() {ClientSceneManager::Instance().LoadScene(std::make_unique<MainScene>()); }, ButtonEvent::Pressed);
}
