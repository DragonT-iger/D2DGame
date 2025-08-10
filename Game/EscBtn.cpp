#include "pch.h"
#include "EscBtn.h"

void EscBtn::Awake()
{
	m_EscBG = GameObject::Find("EscBG");
	m_TitleBtn = GameObject::Find("TitleBtn");
	m_SettingBtn = GameObject::Find("SettingBtn");
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
		}
		else
		{
			m_EscBG->SetActive(false);
			m_TitleBtn->SetActive(false);
			m_SettingBtn->SetActive(false);
		}
	}
}
