#pragma once
#include "Scene.h"
class SceneManager
{
public:
    static SceneManager& Instance();

    void  SetActiveScene(Scene* scene) { m_active = scene; }
    Scene* GetActiveScene() const { return m_active; }

private:
    Scene* m_active = nullptr;
};

inline GameObject* Instantiate(const std::wstring& name = L"GameObject")
{
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Instantiate: active scene is null!");
    return s->CreateGameObject(name);
}

template<typename T, typename... Args>
T* Instantiate(const std::wstring& name, Args&&... args)
{
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Instantiate: active scene is null!");
    GameObject* go = s->CreateGameObject(name);
    return go->AddComponent<T>(std::forward<Args>(args)...);
}