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
	std::wstring score_text = std::to_wstring(GameManager::Instance().GetTotalScore());

	m_Text->SetText(score_text, { 300,50 }, L"Maplestory", D2D1::ColorF::Black);
	m_Text->SetFontSize(15.0f);
}
