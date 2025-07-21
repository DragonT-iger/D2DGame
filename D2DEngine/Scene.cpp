#include "pch.h"
#include "Scene.h"



// -----------------------------------------------------------------------------
// GameObject 생성 / 파괴
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

	// 카메라는 기본적으로 씬에 등록

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

    // 물리 업데이트는 여기서 (aabb obb)


    for (auto& obj : m_gameObjects)
        obj->FixedUpdate(fixedDelta);

    PhysicsManager::Instance().Step(fixedDelta);

    
}

void Scene::LateUpdate(float deltaTime)
{
    //if (!m_active) return;
    for (auto& obj : m_gameObjects)
        obj->LateUpdate(deltaTime);

    auto* cam = GetCamera();

    D2D1::Matrix3x2F viewTM = cam->GetViewTM();

    for (auto& gameObject : m_gameObjects)
    {
		SpriteRenderer* sr = gameObject->GetComponent<SpriteRenderer>();
        if (sr && gameObject->IsActive()) {
            sr->Render(viewTM);
        }

    }

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

void Scene::RegisterCamera(Camera* cam)
{
    if (m_Camera) {
        assert(false && "씬에 카메라가 두대일수 없슴");
    }

    m_Camera = cam;
}
