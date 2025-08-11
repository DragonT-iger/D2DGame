#include "pch.h"
#include "SettingButton.h"
#include "EscBtn.h"

void EscBtn::Awake()
{
	m_EscBG = GameObject::Find("EscBG");
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
		if (!isActive)
		{
			m_EscBG->SetActive(true);
			m_TitleBtn->SetActive(true);
			m_SettingBtn->SetActive(true);
			isActive = true;
		}
		else
		{
			m_EscBG->SetActive(false);
			m_TitleBtn->SetActive(false);
			m_SettingBtn->GetComponent<SettingButton>()->SetOff();
			m_SettingBtn->SetActive(false);
			isActive = false;
		}
	}
}
