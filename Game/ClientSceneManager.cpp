#include "pch.h"
#include "ClientSceneManager.h"
#include "TutorialScene.h"
#include "GameManager.h"

void ClientSceneManager::LoadScene(std::unique_ptr<Scene> scene)
{
    const bool targetIsTutorial = (dynamic_cast<TutorialScene*>(scene.get()) != nullptr);

    if (targetIsTutorial)
    {
        GameManager::Instance().SetGameState(GameManager::GameState::Tutorial);
    }
    else {
        GameManager::Instance().SetGameState(GameManager::GameState::Start);
    }

    SceneManager::Instance().LoadScene(std::move(scene));
}


void ClientSceneManager::ProcessSceneChange()
{
    SceneManager::Instance().ProcessSceneChange();
}