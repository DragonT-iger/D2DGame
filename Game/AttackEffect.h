#pragma once

class Animator;

class AttackEffect : public MonoBehaviour
{
public:
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;

private:
    Animator* m_animator = nullptr;
};