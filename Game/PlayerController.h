// �����ڵ�
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake(); // �ʿ��� �͸� �������̵�
    void Update(float deltaTime) override;
	void OnTriggerEnter(Collider* other) override;



    float m_xSpeed = 0.1f; // x�� �̵� �ӵ�
    float m_ySpeed = 0.1f; // y�� �̵� �ӵ�

private:
	
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
