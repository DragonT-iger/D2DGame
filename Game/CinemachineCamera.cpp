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

    if (SceneManager::Instance().GetDebugMode() == true) {

        auto mouse = Input.GetMouseState();
        Vector2 mousePos{ static_cast<float>(mouse.pos.x), static_cast<float>(mouse.pos.y) };
        if (mouse.MButtonPressed)
        {
            if (!m_isPanning)
            {
                m_isPanning = true;
                m_prevMousePos = mousePos;
            }
            else
            {
                Vector2 delta = mousePos - m_prevMousePos;
                delta.y = -delta.y;
                delta.x *= m_currentZoom;
                delta.y *= m_currentZoom;
                m_panOffset -= delta;
                m_prevMousePos = mousePos;
            }
        }
        else
        {
            m_isPanning = false;
        }

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


    }

    

    if (m_player)
    {
        Vector2 targetPos;
        if (SceneManager::Instance().GetDebugMode() == true) {
            targetPos = m_player->GetComponent<Transform>()->GetPosition() + m_panOffset;
        }
        else {
            targetPos = m_player->GetComponent<Transform>()->GetPosition();
        }

        //std::cout << m_panOffset.x << m_panOffset.y << std::endl;
        Vector2 currentPos = m_transform->GetPosition();

        float   lerpFactor = 1.f - std::exp(-m_followDamping * deltaTime); // 감쇠
        Vector2 newPos = currentPos + (targetPos - currentPos) * lerpFactor;

        m_transform->SetPosition(newPos);
    }


}
