#pragma once

class Inventory;

class TutorialEndTrigger : public MonoBehaviour
{
public:
    void Awake() override;
    void Update(float deltaTime) override;
    void OnTriggerEnter(Collider* other) override;

private:
    Inventory* m_inventory = nullptr;
    bool m_transitionPending = false;
    float m_elapsed = 0.f;
    float m_delay = 3.f;
};