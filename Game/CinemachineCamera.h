#pragma once
class CinemachineCamera : public MonoBehaviour
{
public:
    void   Awake() override;
    void   Start() override;
    void   Update(float deltaTime) override;

    void   SetZoomSpeed(float speed) { m_zoomSpeed = speed; }
    void   SetMinZoom(float value) { m_minZoom = value; }
    void   SetMaxZoom(float value) { m_maxZoom = value; }

private:

	Transform* m_transform = nullptr;



    Camera*      m_Camera = nullptr; // ī�޶� ������Ʈ
    float        m_zoomSpeed = 1.0f;   // �� ĭ(120)�� Ȯ�롤��� ���
    float        m_minZoom = 0.5f;     // �ּ� scale.x
    float        m_maxZoom = 10.0f;    // �ִ� scale.x
};

