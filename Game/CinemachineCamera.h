#pragma once
class CinemachineCamera : public MonoBehaviour
{
public:
    void   Awake() override;
    void   Start() override;
    void   Update(float deltaTime) override;

	void   SetPlayer(GameObject* player) { this->m_player = player; }

private:

	GameObject* m_player = nullptr; // �÷��̾� ������Ʈ

	Transform*  m_transform = nullptr;
    float       m_followDamping = 6.f;


    
    Camera*      m_Camera = nullptr; // ī�޶� ������Ʈ
    float        m_minZoom = 0.5f;     // �ּ� scale.x
    float        m_maxZoom = 10.0f;    // �ִ� scale.x

	float        m_currentZoom = 1.0f; // ���� Ȯ�롤��� ���
    float        m_targetZoom = 1.0f;  // ��ǥ Ȯ�롤��� ���
    float        m_zoomStep = 0.2f;    // Ȯ�롤��� �ܰ�
	float        m_damping = 5.0f;     // �ε巴�� �����ϴ� ����


    Vector2     m_panOffset = Vector2::zero;
    bool        m_isPanning = false;
    Vector2     m_prevMousePos = Vector2::zero;
};

