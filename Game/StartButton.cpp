#include "pch.h"
#include "StartButton.h"

void StartButton::Awake()
{
	
}

void StartButton::Start()
{
	m_button = GetComponent<Button>();

	m_button->AddPressEvent([]() {SceneManager::Instance().LoadScene(L"HSTestScene"); });
}
