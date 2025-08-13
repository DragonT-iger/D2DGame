#include "pch.h"
#include "SettingBtn_Ingame.h"
#include "EscBtn.h"

void EscBtn::Awake()
{
	m_EscBG = GameObject::Find("EscBG");
	m_EscBlurBG = GameObject::Find("EscBlurBG");
	m_ContinueBtn = GameObject::Find("ContinueBtn");
	m_TitleBtn = GameObject::Find("TitleBtn");
	m_SettingBtn = GameObject::Find("settingBtn");
	isActive = false;
}

void EscBtn::Start()
{

}

void EscBtn::Update(float deltaTime)
{
	if (Input.GetKeyPressed(Keycode::ESCAPE))
	{
		if (!m_EscBG->IsActive())
		{
			m_EscBG->SetActive(true);
			m_EscBlurBG->SetActive(true);
			m_ContinueBtn->SetActive(true);
			m_TitleBtn->SetActive(true);
			m_SettingBtn->SetActive(true);
			isActive = true;
		}
		else
		{
			m_EscBG->SetActive(false);
			m_EscBlurBG->SetActive(false);
			m_ContinueBtn->SetActive(false);
			m_TitleBtn->SetActive(false);
			m_SettingBtn->GetComponent<SettingButton_Ingame>()->SetOff();
			m_SettingBtn->SetActive(false);
			isActive = false;
		}
	}
}
