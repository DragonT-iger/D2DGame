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


	Scene::Awake();
}

void TutorialScene::Start()
{
	if (!IsActive())
		return;


	Scene::Start();
}
