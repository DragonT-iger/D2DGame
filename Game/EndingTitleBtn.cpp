#include "pch.h"
#include "TitleScene.h"
#include "ClientSceneManager.h"
#include "EndingTitleBtn.h"

void EndingTitleBtn::Start()
{
	m_button = GetComponent<Button>();
	m_button->AddEvent([this]() { m_button->SetSize({ 370, 255 }); }, ButtonEvent::Idle);
	m_button->AddEvent([this]() {
		m_button->SetSize({ 370, 255 });
		SoundManager::Instance().UI_Shot("1.mp3");
		}, ButtonEvent::Highlight);
	m_button->AddEvent([]() {
		SoundManager::Instance().UI_Shot("2.mp3");
		ClientSceneManager::Instance().LoadScene(std::make_unique<TitleScene>());
		}, ButtonEvent::Pressed);
}