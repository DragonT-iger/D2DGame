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