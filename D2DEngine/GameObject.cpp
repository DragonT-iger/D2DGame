#include "pch.h"

#include "GameObject.h"
#include "MonoBehaviour.h"
#include "Transform.h"

GameObject::GameObject(const std::string& name)
    : m_name{ name }, m_active{ true } {
    this->AddComponent<Transform>();
}

void GameObject::RemoveComponent(Component* component)
{
    if (!component) return;

    if (m_isIterating)
        m_pendingRemove.push_back(component);
    else {
        auto it = std::remove_if(m_components.begin(), m_components.end(),
            [component](auto& up) { return up.get() == component; });
        m_components.erase(it, m_components.end());
    }
}

/* Activation -------------------------------------------------- */
void GameObject::SetActive(bool active) { m_active = active; }
bool GameObject::IsActive() const { return m_active; }



/* Lifecycle Methods -------------------------------------------- */

void GameObject::Awake() {
    m_phase = Phase::Awake;
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            if (IsActive())
                if(mb->IsActive())
                    mb->Awake();
    m_isIterating = false;
    FlushPending();
    m_awakeCalled = true;
}

void GameObject::Start() {
    m_phase = Phase::Start;
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            if(IsActive())
                if (mb->IsActive())
                    mb->Start();
    m_isIterating = false;
    FlushPending();
    m_startCalled = true;
}

void GameObject::Update(float deltaTime) {
    m_phase = Phase::Update;
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            if(IsActive())
                if (mb->IsActive())
                    mb->Update(deltaTime);
    m_isIterating = false;
    FlushPending();
}

void GameObject::FixedUpdate(float fixedDeltaTime) {
    m_phase = Phase::FixedUpdate;
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            if (IsActive())
                if (mb->IsActive())
                    mb->FixedUpdate(fixedDeltaTime);
    m_isIterating = false;
    FlushPending();
}

void GameObject::LateUpdate(float deltaTime) {
    m_phase = Phase::LateUpdate;
    m_isIterating = true;
    for (auto& comp : m_components)
        if (auto* mb = dynamic_cast<MonoBehaviour*>(comp.get()))
            if (IsActive())
                if (mb->IsActive())
                    mb->LateUpdate(deltaTime);
    m_isIterating = false;
    FlushPending();
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
GameObject* GameObject::Find(std::string name)
{
    Scene* curScene = SceneManager::Instance().GetActiveScene();
    return curScene->FindGameObject(name);

}
void GameObject::FlushPending()
{
    /* 1) Add */
    std::vector<Component*> added;
    for (auto& up : m_pendingAdd)
    {
        Component* raw = up.get();
        m_components.emplace_back(std::move(up));
        added.push_back(raw);
    }
    m_pendingAdd.clear();

    bool callAwake = (m_phase == Phase::Awake) || m_awakeCalled;
    bool callStart = (m_phase == Phase::Start) || m_startCalled;

    if (!added.empty())
    {
        for (auto* comp : added)
            if (auto* mb = dynamic_cast<MonoBehaviour*>(comp))
            {
                if (callAwake && IsActive() && mb->IsActive())
                    mb->Awake();
                if (callStart && IsActive() && mb->IsActive())
                    mb->Start();
            }
    }

    /* 2) Remove */
    for (auto* dead : m_pendingRemove)
    {
        auto it = std::remove_if(m_components.begin(), m_components.end(),
            [dead](auto& up) { return up.get() == dead; });
        m_components.erase(it, m_components.end());
    }
    m_pendingRemove.clear();
}
