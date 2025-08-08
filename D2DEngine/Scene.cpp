#include "pch.h"
#include "Scene.h"
#include "../Game/CinemachineCamera.h"




// -----------------------------------------------------------------------------
// GameObject 생성 / 파괴
// -----------------------------------------------------------------------------

GameObject* Scene::CreateGameObject(const std::string& name)
{
    auto go = std::make_unique<GameObject>(name);
    GameObject* raw = go.get();

    if (m_isIterating)
        m_pendingAdd.emplace_back(std::move(go));
    else
        m_gameObjects.emplace_back(std::move(go));
    return raw;
}


void Scene::Destroy(GameObject* object)
{
    if (object)
        m_pendingDestroy.push_back(object);
}

// -----------------------------------------------------------------------------
// Lifecycle dispatch
// -----------------------------------------------------------------------------

void Scene::Awake()
{
    //if (!m_active) return;


    m_phase = ScenePhase::Awake;

    GameObject* camera = CreateGameObject("Camera");
    camera->AddComponent<Camera>();
    camera->AddComponent<CinemachineCamera>();

    // 카메라는 기본적으로 씬에 등록

    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->Awake();
    m_isIterating = false;
    FlushPending();
}

void Scene::Start()
{

    //if (!m_active) return;


    m_phase = ScenePhase::Start;
    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->Start();
    m_isIterating = false;
    FlushPending();
}

void Scene::Update(float deltaTime)
{
    //if (!m_active) return;
	m_phase = ScenePhase::Update;
    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->Update(deltaTime);
    m_isIterating = false;
    FlushPending();

    SoundManager::Instance().Update();
    if (m_deltatime >= 1000.f)
    {
        m_deltatime = 0.0f;
        m_fps = m_frameCount;
        m_frameCount = 0;
    }
    else
    {
        m_deltatime += deltaTime * 1000.0f;
        m_frameCount++;
    }
}

void Scene::FixedUpdate(float fixedDelta)
{
    //if (!m_active) return;

	m_phase = ScenePhase::FixedUpdate;

    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->FixedUpdate(fixedDelta);
    m_isIterating = false;
    FlushPending();

    PhysicsManager::Instance().Step(fixedDelta);

    
}

void Scene::LateUpdate(float deltaTime)
{
    //if (!m_active) return;
	m_phase = ScenePhase::LateUpdate;
    m_isIterating = true;
    for (auto& obj : m_gameObjects) obj->LateUpdate(deltaTime);
    m_isIterating = false;
    FlushPending();

    

    /*if (!cam) std::cout << "카메라가 없음" << std::endl;
    else std::cout << "카메라가 있음" << std::endl;*/

    //assert(cam && "카메라 없음"); 카메라는 일단 없어도 되잖아?


    // 렌더링 로직은 여기에


    /* example


    const auto& view = cam->GetViewTM();
    for (auto& go : m_gameObjects)
        if (auto* sr = go->GetComponent<SpriteRenderer>())
            sr->Render(r, view);


    */
}

void Scene::Render()
{

    //if (!m_active) return;

    FlushPending();

	m_phase = ScenePhase::Render;
    SetRenderQ();

	auto* cam = GetCamera();

	D2D1::Matrix3x2F viewTM = cam->GetViewTM();

    //object render
    for(auto& info : m_renderQ)
    {
        if (info.m_bitmap == nullptr) continue;
        D2D1::Matrix3x2F renderTM = GetRenderTM(info.isFlip);
        D2D1::Matrix3x2F mWV = renderTM * info.m_transform->GetWorldMatrix() * viewTM;
        D2DRenderer::Instance().SetTransform(mWV);
        //D2DRenderer::Instance().DrawCircle(0, 0, info.radius, RGB(255, 0, 0));
        D2DRenderer::Instance().DrawBitmap(info.m_bitmap.Get(), info.m_destRect, info.m_srcRect, info.opacity);
	}

    if (SceneManager::Instance().GetDebugMode())
    {
		for (const auto& info : m_colliderQ)
		{
			if (info.m_collider)
			{
				Vector2 s = info.m_transform->GetScale();
				Vector2 p = info.m_transform->GetPosition();
				D2D1::Matrix3x2F renderTM = GetRenderTM();
				D2D1::Matrix3x2F worldTM;
				if (info.m_transform->GetParent()) {
					Vector2 v = info.m_transform->GetParent()->GetPosition();
					worldTM = D2D1::Matrix3x2F::Scale(s.x, s.x) * D2D1::Matrix3x2F::Translation({ p.x, p.y }) * D2D1::Matrix3x2F::Translation(v.x, v.y);
				}
				else
				{
					worldTM = D2D1::Matrix3x2F::Scale(s.x, s.x) * D2D1::Matrix3x2F::Translation({ p.x, p.y });
				}

				D2D1::Matrix3x2F mWV = renderTM * worldTM * viewTM;
				D2DRenderer::Instance().SetTransform(mWV);
				info.m_collider->DrawCollider();
			}
		}
    }
    
    //그리드 출력
	if (SceneManager::Instance().GetDebugMode() && m_isGridOn)
	{
        float unit = 100.f;

		RECT sr;
		::GetClientRect(D2DRenderer::Instance().GetHandle(), &sr);
        float w = static_cast<float>(sr.right - sr.left);
		float h = static_cast<float>(sr.bottom - sr.top);

        D2D1::Matrix3x2F invViewTM = viewTM;
        invViewTM.Invert();

        D2D1_POINT_2F topLeft = D2D1::Point2F(0, 0);
        D2D1_POINT_2F topRight = D2D1::Point2F(w, 0);
        D2D1_POINT_2F bottomLeft = D2D1::Point2F(0, h);
        D2D1_POINT_2F bottomRight = D2D1::Point2F(w, h);

        topLeft = invViewTM.TransformPoint(topLeft);
        topRight = invViewTM.TransformPoint(topRight);
        bottomLeft = invViewTM.TransformPoint(bottomLeft);
        bottomRight = invViewTM.TransformPoint(bottomRight);

		float startX = std::floor(topLeft.x / unit) * unit;
		float endX = std::ceil(bottomRight.x / unit) * unit;
		float startY = std::floor(topLeft.y / unit) * unit;
		float endY = std::ceil(bottomRight.y / unit) * unit;

		D2DRenderer::Instance().SetTransform(viewTM);
        //x축 그리드
		for (float x = startX; x <= endX; x += unit)
		{
			D2DRenderer::Instance().DrawLine(x, startY, x, endY, D2D1::ColorF::Black);
		}
        //y축 그리드
		for (float y = startY; y >= endY; y -= unit)
		{
			D2DRenderer::Instance().DrawLine(startX, y, endX, y, D2D1::ColorF::Black);
		}
	}

    //ui render
    D2DRenderer::Instance().SetTransform(D2D1::Matrix3x2F::Identity());
    for (auto& info : m_UIRenderQ)
    {
        if (info.m_bitmap.Get() != nullptr) {
            D2DRenderer::Instance().DrawBitmap(info.m_bitmap.Get(), info.m_destRect, info.m_srcRect);
            if (info.m_text.data())
            {
				D2DRenderer::Instance().SetFont(info.m_font.data(), info.fontSize);
				D2DRenderer::Instance().DrawMessage(info.m_text.data(), info.m_layoutRect, info.m_color);
                if(SceneManager::Instance().GetDebugMode())
				    D2DRenderer::Instance().DrawRectangle(info.m_layoutRect.left, info.m_layoutRect.top, info.m_layoutRect.right, info.m_layoutRect.bottom, D2D1::ColorF::Red);
            }
        }
        else if (info.m_text.data())
        {
            D2DRenderer::Instance().SetFont(info.m_font.data(), info.fontSize);
            D2DRenderer::Instance().DrawMessage(info.m_text.data(), info.m_layoutRect, info.m_color);
            if (SceneManager::Instance().GetDebugMode())
                D2DRenderer::Instance().DrawRectangle(info.m_layoutRect.left, info.m_layoutRect.top, info.m_layoutRect.right, info.m_layoutRect.bottom, D2D1::ColorF::Red);
        }
    }

    if (SceneManager::Instance().GetDebugMode())
    {
		D2DRenderer::Instance().SetFont(L"맑은고딕", 15.0f);
		std::wstring fps = L"fps : " + std::to_wstring(m_fps) + L" / " + std::to_wstring(static_cast<int>(m_deltatime));
		D2D1_RECT_F layout = { 0, 0, 150, 50 };
		D2DRenderer::Instance().DrawMessage(fps.c_str(), layout, D2D1::ColorF::Blue);
    }
    
	m_renderQ.clear();
    m_colliderQ.clear();
    m_UIRenderQ.clear();
}

void Scene::UnInitialize()
{
    //m_pendingAdd.clear();
    //m_pendingDestroy.clear();
    //m_gameObjects.clear();
    //m_renderQ.clear();
    //m_UIRenderQ.clear();
    //m_colliderQ.clear();
    //m_Camera = nullptr;
    //m_gameObjects.clear();
}

void Scene::SetRenderQ()
{
    m_isIterating = true;
    for (auto& obj : m_gameObjects)
    {
        if(!obj->IsActive())
            continue;
        const auto& spRender = obj->GetComponent<SpriteRenderer>();
        const auto& collider = obj->GetComponent<Collider>();
        if (spRender && spRender->IsActive())
        {
            m_renderQ.push_back(spRender->GetRenderInfo());
        }
        else if (auto* img = obj->GetComponent<Image>())
        {
            if (img && img->IsActive()){
                m_UIRenderQ.push_back(img->GetRenderInfo());
            }
            if (auto* txt = obj->GetComponent<Text>())
            {
				if (txt->IsActive()) {
					m_UIRenderQ.push_back(txt->GetRenderInfo());
				}
            }
        }
        else if (auto* txt = obj->GetComponent<Text>())
        {
			if (txt && txt->IsActive()) {
				m_UIRenderQ.push_back(txt->GetRenderInfo());
			}
        }
        if (collider && collider->IsActive()){
            m_colliderQ.push_back(collider->GetColliderInfo());
        }
    }

    std::sort(m_renderQ.begin(), m_renderQ.end());
    std::sort(m_UIRenderQ.begin(), m_UIRenderQ.end());
    m_isIterating = false;
    FlushPending();
}

void Scene::RegisterCamera(Camera* cam)
{
    //if (m_Camera) {
        //assert(false && "씬에 카메라가 두대일수 없슴");

        // std::cout << "씬 로드 두번하면 카메라가 두번생기는데 그건 뭐 괜찮으니까 그냥 패스 << std::endl;
    //}

    m_Camera = cam;
}

D2D1::Matrix3x2F Scene::GetRenderTM(bool isFlip, float offsetX, float offsetY)
{
    float scaleX = isFlip ? -1.0f : 1.0f;

    offsetX = isFlip ? -offsetX : offsetX;
    offsetY = -offsetY;

    return D2D1::Matrix3x2F::Scale(scaleX, -1.0f) * D2D1::Matrix3x2F::Translation(offsetX, offsetY);
}

void Scene::OnDisable()
{
    //UnInitialize();
    
}

GameObject* Scene::FindGameObject(std::string name)
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
        if ((*it)->GetName() == name) {
            return (*it).get();
        }
    }

    return nullptr;
}

void Scene::FlushPending()
{
    std::vector<GameObject*> added;
    for (auto& up : m_pendingAdd)
    {
        GameObject* raw = up.get();
        m_gameObjects.emplace_back(std::move(up));
        added.push_back(raw);
    }
    m_pendingAdd.clear();

    if (m_phase == ScenePhase::Awake)
    {
        for (auto* obj : added)
            obj->Awake();
    }
    else
    {
        for (auto* obj : added)
        {
            obj->Awake();
            obj->Start();

        }
    }

    for (auto* dead : m_pendingDestroy)
    {
        auto it = std::remove_if(m_gameObjects.begin(), m_gameObjects.end(),
            [dead](auto& up) { return up.get() == dead; });
        m_gameObjects.erase(it, m_gameObjects.end());
    }
    m_pendingDestroy.clear();
}
