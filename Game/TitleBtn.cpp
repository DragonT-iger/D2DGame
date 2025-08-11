#include "pch.h"
#include "TitleScene.h"
#include "TitleBtn.h"

void TitleBtn::Start()
{
	m_button = GetComponent<Button>();
	m_button->AddEvent([]() {SceneManager::Instance().LoadScene(std::make_unique<TitleScene>()); }, ButtonEvent::Pressed);
}
