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



    Camera*      m_Camera = nullptr; // 카메라 컴포넌트
    float        m_zoomSpeed = 1.0f;   // 한 칸(120)당 확대·축소 배수
    float        m_minZoom = 0.5f;     // 최소 scale.x
    float        m_maxZoom = 10.0f;    // 최대 scale.x
};

