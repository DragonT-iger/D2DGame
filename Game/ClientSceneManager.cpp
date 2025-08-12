#include "pch.h"
#include "ClientSceneManager.h"
#include "TitleScene.h"
#include "MainScene.h"
#include "EndingScene.h"
#include "TutorialScene.h"
#include "GameManager.h"

void ClientSceneManager::LoadScene(std::unique_ptr<Scene> scene)
{
    const bool targetIsTitle = (dynamic_cast<TitleScene*>(scene.get()) != nullptr);
    const bool targetIsTutorial = (dynamic_cast<TutorialScene*>(scene.get()) != nullptr);
    const bool targetIsMain =     (dynamic_cast<MainScene*>(scene.get()) != nullptr);
    const bool targetIsEnd =         (dynamic_cast<EndingScene*>(scene.get()) != nullptr);

    if (targetIsTitle)
    {
        GameManager::Instance().ResetTotalScore();
        GameManager::Instance().SetGameState(GameManager::GameState::Title);
    }
    else if (targetIsTutorial)
    {
        GameManager::Instance().SetGameState(GameManager::GameState::Tutorial);
    }
    else if(targetIsMain)
    {
        GameManager::Instance().SetGameState(GameManager::GameState::Main);
    }
    else if (targetIsEnd)
    {
        GameManager::Instance().SetGameState(GameManager::GameState::End);
    }

    SceneManager::Instance().LoadScene(std::move(scene));
}


void ClientSceneManager::ProcessSceneChange()
{
    SceneManager::Instance().ProcessSceneChange();
}