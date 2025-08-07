#include "pch.h"
#include "Player.h"
#include "HungryGauge.h"

void HungryGauge::Awake()
{
	m_gauge = GetComponent<Slide_Bar>();
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer()->GetComponent<Player>();
	auto img = GetComponent<Image>();
	img->SetBitmap(ResourceManager::Instance().LoadTexture("gaugebar_blue.png"), { 250, 30 });
	img->SetOrderInLayer(3);
}

void HungryGauge::Update(float deltaTime)
{
	m_gauge->UpdateWidthRatio(m_player->GetFullness() / 1000.f);
}
