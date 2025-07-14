#pragma once


/// <summary>
/// ���� 1 �� ī�޶� ������Ʈ
/// </summary>
class Camera : public MonoBehaviour
{
public:
    Camera() = default;                                    
    virtual ~Camera();

    void  SetZoom(float zoom) { m_zoom = zoom; }
    float GetZoom()        const { return m_zoom; }

    const D2D1::Matrix3x2F& GetViewTM() const { return m_viewTM; }

    // MonoBehaviour �������̵� ������������������
    void LateUpdate(float deltaTime) override;  

protected:
    void Awake() override;                      

private:
    Camera* s_main = nullptr; 

    D2D1::Matrix3x2F m_viewTM = D2D1::Matrix3x2F::Identity();
    float            m_zoom = 1.f;
};

