#include "pch.h"
#include "GameManager.h"
#include "UI_Score.h"
#include "Text.h"

void UI_Score::Awake()
{
	m_Text = GetComponent<Text>();
}

void UI_Score::Update(float deltaTime)
{
	std::wstring score_text = L"Score : " + std::to_wstring(GameManager::Instance().GetTotalScore());

	m_Text->SetText(score_text, { 260,50 }, L"Maplestory");
	m_Text->SetFontSize(40.0f);
}
