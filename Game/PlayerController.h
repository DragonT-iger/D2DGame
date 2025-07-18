// PlayerController.h
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake() override;
    void Start() override;
    void Update(float deltaTime) override;

private:
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
