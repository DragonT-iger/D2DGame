#include "pch.h"
#include "StartButton.h"
#include "MainScene.h"

void StartButton::Awake()
{
	
}

void StartButton::Start()
{
	m_button = GetComponent<Button>();

	m_button->AddPressEvent([]() {SceneManager::Instance().LoadScene(std::make_unique<MainScene>()); }, ButtonEvent::Pressed);
}
