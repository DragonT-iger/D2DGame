// 예시코드
#pragma once

class PlayerController : public MonoBehaviour
{
public:
    void Awake(); // 필요한 것만 오버라이드
    void Update(float deltaTime) override;
	void OnTriggerEnter(Collider* other) override;



    float m_xSpeed = 0.1f; // x축 이동 속도
    float m_ySpeed = 0.1f; // y축 이동 속도

private:
	
    Transform* m_transform = nullptr;
    SpriteRenderer* m_spriteRenderer = nullptr;
};
