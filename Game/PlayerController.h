// �����ڵ�
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake(); // �ʿ��� �͸� �������̵�
    void Update(float deltaTime) override;

private:
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
