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
    int wheelDelta = InputManager::Instance().GetWheelDelta();
    if (wheelDelta != 0)
    {
        int ticks = wheelDelta / WHEEL_DELTA;     // ±1, ±2 …
        float factorPerTick = (wheelDelta > 0) ? (1.f - m_zoomStep)
            : (1.f + m_zoomStep);
        // 여러 틱 들어오면 누적 반영
        m_targetZoom *= std::pow(factorPerTick, std::abs(ticks));
        m_targetZoom = std::clamp(m_targetZoom, m_minZoom, m_maxZoom);
    }

    // ── 부드럽게 수렴 ──
    m_currentZoom += (m_targetZoom - m_currentZoom) * (1.f - std::exp(-m_damping * deltaTime));

    // 둘 다 같은 비율이면 화면이 안 찌그러지므로 x,y 모두 적용
    Vector2 newScale{ m_currentZoom, m_currentZoom };
    m_transform->SetScale(newScale);
}
