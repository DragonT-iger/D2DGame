#include "pch.h"
#include "Camera.h"
#include "Scene.h"



Camera::~Camera()
{
    // ���� ��� �ִٸ� ��� ����
    if (Scene* s = SceneManager::Instance().GetActiveScene())
        s->UnregisterCamera(this);
}

void Camera::Awake()
{
    // Ȱ�� ���� �ڽ��� ���� ī�޶�� ���
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Camera::Awake - Active Scene is null!");
    s->RegisterCamera(this);
}

void Camera::LateUpdate(float deltaTime)
{
    auto* tr = GetComponent<Transform>();
    D2D1::Matrix3x2F invWorld = tr->GetWorldMatrix();
    invWorld.Invert();

    // ��(Scale) ����
    D2D1::Matrix3x2F zoomTM = D2D1::Matrix3x2F::Scale(m_zoom, m_zoom);
    m_viewTM = invWorld * zoomTM;
    // �����Բ��� ��� �Ǿ��ִ��� �̰� ��Ƽ�÷��� ���� �־�ߵ��� �𸣰ڳ�
    // �ϴ� ���� �̽� ����� �׶� ���� �׸� ���� ���ϰ� Ŀ������ ����
    // ��� ī�޶� �����̴� �����ϼ��� �ְ�
}
