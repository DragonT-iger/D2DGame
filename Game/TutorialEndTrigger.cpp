#include "pch.h"
#include "TutorialEndTrigger.h"
#include "Inventory.h"
#include "GameManager.h"
#include "ClientSceneManager.h"
#include "MainScene.h"

void TutorialEndTrigger::Awake()
{
    m_inventory = GameObject::Find("Inventory")->GetComponent<Inventory>();
}

void TutorialEndTrigger::Update(float deltaTime)
{
    if (!m_transitionPending)
        return;

    m_elapsed += deltaTime;
    if (m_elapsed >= m_delay)
    {
        ClientSceneManager::Instance().LoadScene(std::make_unique<MainScene>());
        m_transitionPending = false;
    }
}

void TutorialEndTrigger::OnTriggerEnter(Collider* other)
{
    if (m_transitionPending)
        return;

    if (other->GetOwner()->GetTag() != "Player" || m_inventory == nullptr)
        return;

    GameManager::Instance().ReceiveScore(m_inventory->SubMissonItem());
    m_transitionPending = true;
    m_elapsed = 0.f;
}
