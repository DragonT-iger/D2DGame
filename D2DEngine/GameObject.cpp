#include "pch.h"

#include "GameObject.h"
#include "MonoBehaviour.h"
#include "Transform.h"

GameObject::GameObject(const std::wstring& name)
    : m_name{ name }, m_active{ true } {
    this->AddComponent<Transform>();
}

/* Activation -------------------------------------------------- */
void GameObject::SetActive(bool active) { m_active = active; }
bool GameObject::IsActive() const { return m_active; }



/* Lifecycle Methods -------------------------------------------- */

void GameObject::Awake() {
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->Awake();
        }
    }
}

void GameObject::Start() {
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->Start();
        }
    }
}

void GameObject::Update(float deltaTime) {
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->Update(deltaTime);
        }
    }
}

void GameObject::FixedUpdate(float fixedDeltaTime) {
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->FixedUpdate(fixedDeltaTime);
        }
    }
}

void GameObject::LateUpdate(float deltaTime) {
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->LateUpdate(deltaTime);
        }
    }
}

void GameObject::BroadcastTriggerEnter(Collider* other)
{
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->OnTriggerEnter(other);
        }
	}
}

void GameObject::BroadcastTriggerStay(Collider* other)
{
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->OnTriggerStay(other);
        }
	}
}

void GameObject::BroadcastTriggerExit(Collider* other)
{
    for (auto& comp : m_components) {
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get())) {
            mb->OnTriggerExit(other);
        }
	}
}
