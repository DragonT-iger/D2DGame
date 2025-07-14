#pragma once


/// <summary>
/// 씬당 1 대 카메라 컴포넌트
/// </summary>
class Camera : public MonoBehaviour
{
public:
    Camera() = default;                                    
    virtual ~Camera();

    void  SetZoom(float zoom) { m_zoom = zoom; }
    float GetZoom()        const { return m_zoom; }

    const D2D1::Matrix3x2F& GetViewTM() const { return m_viewTM; }

    // MonoBehaviour 오버라이드 ─────────
    void LateUpdate(float deltaTime) override;  

protected:
    void Awake() override;                      

private:
    Camera* s_main = nullptr; 

    D2D1::Matrix3x2F m_viewTM = D2D1::Matrix3x2F::Identity();
    float            m_zoom = 1.f;
};

