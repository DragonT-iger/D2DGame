#include "pch.h"
#include "CinemachineCamera.h"


void CinemachineCamera::Awake()
{
	m_transform = GetComponent<Transform>();
	if (!m_transform)
	{
		assert(false && "CinemachineCamera::Awake - Transform component is missing!");
		return;
	}
}

void CinemachineCamera::Start()
{

	m_Camera = GetComponent<Camera>();
}

void CinemachineCamera::Update(float deltaTime)
{
#ifdef _DEBUG

    int wheelDelta = InputManager::Instance().GetWheelDelta();
    if (wheelDelta != 0)
    {
        int ticks = wheelDelta / WHEEL_DELTA;    
        float factorPerTick = (wheelDelta > 0) ? (1.f - m_zoomStep)
            : (1.f + m_zoomStep);
        m_targetZoom *= std::pow(factorPerTick, std::abs(ticks));
        m_targetZoom = std::clamp(m_targetZoom, m_minZoom, m_maxZoom);
    }

    // ── 부드럽게 수렴 ──
    m_currentZoom += (m_targetZoom - m_currentZoom) * (1.f - std::exp(-m_damping * deltaTime));

    // 둘 다 같은 비율이면 화면이 안 찌그러지므로 x,y 모두 적용
    Vector2 newScale{ m_currentZoom, m_currentZoom };
    m_transform->SetScale(newScale);



    if (m_player)
    {
        Vector2 targetPos = m_player->GetComponent<Transform>()->GetPosition();
        Vector2 currentPos = m_transform->GetPosition();

        float   lerpFactor = 1.f - std::exp(-m_followDamping * deltaTime); // 감쇠
        Vector2 newPos = currentPos + (targetPos - currentPos) * lerpFactor;

        m_transform->SetPosition(newPos);
    }


#endif
}
