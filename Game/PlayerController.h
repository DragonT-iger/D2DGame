// 예시코드
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake(); // 필요한 것만 오버라이드
    void Update(float deltaTime) override;

private:
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
