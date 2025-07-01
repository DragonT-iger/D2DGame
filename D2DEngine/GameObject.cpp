#include "pch.h"

#include "GameObject.h"
#include "MonoBehaviour.h"

GameObject::GameObject(const std::wstring& name)
    : m_name{ name }, m_active{ true }
{
}

/* Activation -------------------------------------------------- */
void GameObject::SetActive(bool active) { m_active = active; }
bool GameObject::IsActive() const { return m_active; }

/* Lifecycle dispatch ----------------------------------------- */
void GameObject::Awake()
{
    for (auto& c : m_components) c->Awake();
}
void GameObject::Start()
{
    for (auto& c : m_components) c->Start();
}
void GameObject::FixedUpdate(float deltaTime)
{
    for (auto& c : m_components) c->FixedUpdate(deltaTime);
}
void GameObject::Update(float deltaTime)
{
    for (auto& c : m_components) c->Update(deltaTime);
}
void GameObject::LateUpdate(float deltaTime)
{
    for (auto& c : m_components) c->LateUpdate(deltaTime);
}
