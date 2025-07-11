#include "pch.h"
#include "Scene.h"



// -----------------------------------------------------------------------------
// GameObject »ý¼º / ÆÄ±«
// -----------------------------------------------------------------------------

GameObject* Scene::CreateGameObject(const std::wstring& name)
{
    auto go = std::make_unique<GameObject>(name);
    GameObject* raw = go.get();           

    m_gameObjects.emplace_back(std::move(go));
    return raw;
}

//void Scene::Destroy(GameObject* object)
//{
//
//}

// -----------------------------------------------------------------------------
// Lifecycle dispatch
// -----------------------------------------------------------------------------

void Scene::Awake()
{
    if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->Awake();
}

void Scene::Start()
{
    if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->Start();
}

void Scene::Update(float deltaTime)
{
    if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->Update(deltaTime);
}

void Scene::FixedUpdate(float fixedDelta)
{
    if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->FixedUpdate(fixedDelta);
}

void Scene::LateUpdate(float deltaTime)
{
    if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->LateUpdate(deltaTime);
}
