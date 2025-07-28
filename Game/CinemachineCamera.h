#pragma once
class CinemachineCamera : public MonoBehaviour
{
public:
    void   Awake() override;
    void   Start() override;
    void   Update(float deltaTime) override;

private:

	Transform* m_transform = nullptr;



    Camera*      m_Camera = nullptr; // 카메라 컴포넌트
    float        m_minZoom = 0.5f;     // 최소 scale.x
    float        m_maxZoom = 10.0f;    // 최대 scale.x

	float        m_currentZoom = 1.0f; // 현재 확대·축소 배수
    float        m_targetZoom = 1.0f;  // 목표 확대·축소 배수
    float        m_zoomStep = 0.1f;    // 확대·축소 단계
	float        m_damping = 5.0f;     // 부드럽게 수렴하는 정도
};

