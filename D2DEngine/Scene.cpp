#include "pch.h"
#include "Scene.h"



// -----------------------------------------------------------------------------
// GameObject ���� / �ı�
// -----------------------------------------------------------------------------

GameObject* Scene::CreateGameObject(const std::wstring& name)
{
    auto go = std::make_unique<GameObject>(name);
    GameObject* raw = go.get();

    m_gameObjects.emplace_back(std::move(go));
    return raw;
}

//void Scene::Destroy(GameObject* object)
//{
//
//}

// -----------------------------------------------------------------------------
// Lifecycle dispatch
// -----------------------------------------------------------------------------

void Scene::Awake()
{
    //if (!m_active) return;

    GameObject* camera = CreateGameObject(L"Camera");
    camera->AddComponent<Camera>();

	// ī�޶�� �⺻������ ���� ���

    for (auto& obj : m_gameObjects)
        obj->Awake();
}

void Scene::Start()
{
    //if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->Start();
}

void Scene::Update(float deltaTime)
{
    //if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->Update(deltaTime);
}

void Scene::FixedUpdate(float fixedDelta)
{
    //if (!m_active) return;


    for (auto& obj : m_gameObjects)
        obj->FixedUpdate(fixedDelta);

    PhysicsManager::Instance().Step(fixedDelta);

    
}

void Scene::LateUpdate(float deltaTime)
{
    //if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->LateUpdate(deltaTime);

    

	/*if (!cam) std::cout << "ī�޶� ����" << std::endl;
	else std::cout << "ī�޶� ����" << std::endl;*/

    //assert(cam && "ī�޶� ����"); ī�޶�� �ϴ� ��� ���ݾ�?


    // ������ ������ ���⿡


    /* example
    

    const auto& view = cam->GetViewTM();
    for (auto& go : m_gameObjects)
        if (auto* sr = go->GetComponent<SpriteRenderer>())
            sr->Render(r, view);
    
    
    */
}

void Scene::Render()
{
    SetRenderQ();

	auto* cam = GetCamera();

	D2D1::Matrix3x2F viewTM = cam->GetViewTM();

    for(auto& info : m_renderQ)
    {
        D2D1::Matrix3x2F mWV = info.worldTM * viewTM;
        D2DRenderer::Instance().SetTransform(mWV);
        D2DRenderer::Instance().DrawBitmap(info.m_bitmap.Get(), info.m_destRect, info.m_srcRect);
	}

	m_renderQ.clear();
}

void Scene::UnInitialize()
{
    m_gameObjects.clear();
}

void Scene::SetRenderQ()
{
    for (auto& obj : m_gameObjects)
    {
        const auto& spRender = obj->GetComponent<SpriteRenderer>();
        if (spRender)
        {
            m_renderQ.push_back(spRender->GetRenderInfo());
        }
    }
}

void Scene::RegisterCamera(Camera* cam)
{
    if (m_Camera) {
        assert(false && "���� ī�޶� �δ��ϼ� ����");
    }

    m_Camera = cam;
}
