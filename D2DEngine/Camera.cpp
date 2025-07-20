#include "pch.h"
#include "Camera.h"
#include "Scene.h"



Camera::~Camera()
{
    // 씬이 살아 있다면 등록 해제
    if (Scene* s = SceneManager::Instance().GetActiveScene())
        s->UnregisterCamera(this);
}

void Camera::Awake()
{
    // 활성 씬에 자신을 메인 카메라로 등록
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Camera::Awake - Active Scene is null!");
    s->RegisterCamera(this);
}

void Camera::LateUpdate(float deltaTime)
{
    auto* tr = GetComponent<Transform>();
    D2D1::Matrix3x2F invWorld = tr->GetWorldMatrix();
    invWorld.Invert();

    // 줌(Scale) 적용
    D2D1::Matrix3x2F zoomTM = D2D1::Matrix3x2F::Scale(m_zoom, m_zoom);
    m_viewTM = invWorld * zoomTM;
    // 교수님꺼가 어떻게 되어있더라 이거 더티플레그 어찌 넣어야될지 모르겠네
    // 일단 성능 이슈 생기면 그때 하자 그리 연산 부하가 커보이진 않음
    // 계속 카메라 움직이는 게임일수도 있고
}
