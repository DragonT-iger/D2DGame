#include "pch.h"
#include "TutorialScene.h"
#include "Player.h"
#include "PlayerAnimator.h"
#include "PlayerController.h"
#include "CinemachineCamera.h"
#include "Crop.h"
#include "Bush.h"
#include "FarmerManager.h"
#include "InventorySlot.h"
#include "Inventory.h"
#include "PlayerSound.h"
#include "YSort.h"
#include "GameManager.h"
#include "HungryGauge.h"
#include "Baby.h"
#include "UI_Score.h"
#include "SubMissionArea.h"
#include "EscBtn.h"
#include "TitleBtn.h"
#include "SettingButton.h"
#include "AcceptSetting.h"
#include "QuitSetting.h"

void TutorialScene::Awake()
{
	if (!IsActive())
		return;


    m_background = Instantiate("background");
    auto sr = m_background->AddComponent<SpriteRenderer>();
    sr->SetBitmap(ResourceManager::Instance().LoadTexture("TutorialBackground.png"));
    sr->SetOrderInLayer(-200000);
    m_background->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

    m_outRangeUp = Instantiate("outRangeUp");
    m_outRangeDown = Instantiate("outRangeDown");
    m_outRangeRight = Instantiate("outRangeRight");
    m_outRangeLeft = Instantiate("outRangeLeft");

    m_outRangeUp->SetTag("OutRange");
    m_outRangeDown->SetTag("OutRange");
    m_outRangeRight->SetTag("OutRange");
    m_outRangeLeft->SetTag("OutRange");

    auto box = m_outRangeUp->AddComponent<BoxCollider>();
    box->SetSize({ 9542 , 100 });
    box = m_outRangeDown->AddComponent<BoxCollider>();
    box->SetSize({ 9542 , 100 });
    box = m_outRangeRight->AddComponent<BoxCollider>();
    box->SetSize({ 100 , 1284 });
    box = m_outRangeLeft->AddComponent<BoxCollider>();
    box->SetSize({ 100 , 1284 });

    m_outRangeUp->GetComponent<Transform>()->SetPosition({ 0, 692 });
    m_outRangeDown->GetComponent<Transform>()->SetPosition({ 0, -692 });
    m_outRangeRight->GetComponent<Transform>()->SetPosition({ 4821, 0 });
    m_outRangeLeft->GetComponent<Transform>()->SetPosition({ -4821, 0 });


	Scene::Awake();
}

void TutorialScene::Start()
{
	if (!IsActive())
		return;


	Scene::Start();
}
