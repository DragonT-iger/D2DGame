#pragma once
class CinemachineCamera : public MonoBehaviour
{
public:
    void   Awake() override;
    void   Start() override;
    void   Update(float deltaTime) override;

private:

	Transform* m_transform = nullptr;



    Camera*      m_Camera = nullptr; // ī�޶� ������Ʈ
    float        m_minZoom = 0.5f;     // �ּ� scale.x
    float        m_maxZoom = 10.0f;    // �ִ� scale.x

	float        m_currentZoom = 1.0f; // ���� Ȯ�롤��� ���
    float        m_targetZoom = 1.0f;  // ��ǥ Ȯ�롤��� ���
    float        m_zoomStep = 0.1f;    // Ȯ�롤��� �ܰ�
	float        m_damping = 5.0f;     // �ε巴�� �����ϴ� ����
};

