#include "pch.h"
#include "TitleScene.h"
#include "TitleBtn.h"
#include "ClientSceneManager.h"

void TitleBtn::Start()
{
	m_button = GetComponent<Button>();
	m_button->AddEvent([]() {
		SoundManager::Instance().UI_Shot("2.mp3"); 
		ClientSceneManager::Instance().LoadScene(std::make_unique<TitleScene>()); 
		}, ButtonEvent::Pressed);
}
