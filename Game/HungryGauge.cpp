#include "pch.h"
#include "Player.h"
#include "HungryGauge.h"

void HungryGauge::Awake()
{
	m_gauge = GetComponent<Slide_Bar>();
	m_player = SceneManager::Instance().GetActiveScene()->GetPlayer()->GetComponent<Player>();
	auto img = GetComponent<Image>();
	img->SetBitmap(ResourceManager::Instance().LoadTexture("guage_fill.png"), { 198, 35 });
	img->SetOrderInLayer(3);
}

void HungryGauge::Update(float deltaTime)
{
	auto fullness = m_player->GetFullness() / 3000.f;
	m_gauge->UpdateWidthRatio(fullness);
}
