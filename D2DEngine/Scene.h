/// 날짜 / 이름 / 수정내용
/// 2025-07-11 권용범 최초버전 작성
#pragma once

#include "GameObject.h"

/// <summary>
/// 라이프 사이클을 지원하는 씬
/// </summary>
class Scene
{
public:
    explicit Scene(const std::wstring& name = L"NewScene") : m_name(name) {};
    virtual ~Scene() = default;

    GameObject* CreateGameObject(const std::wstring& name = L"GameObject");

	//void Destroy(GameObject* object); 필요하면 나중에 구현 웬만하면 삭제 안해도 되긴 함 그냥 SetActive(false)로 처리하셈 
    //왜냐면 엔진단에서 처리해야 하는게 좀 생김

    // ---------- Lifecycle ----------
    virtual void Awake();
    virtual void Start();
    virtual void Update(float deltaTime);
    virtual void FixedUpdate(float fixedDelta);
    virtual void LateUpdate(float deltaTime);

    // ---------- Misc ----------
    void SetActive(bool active) { m_active = active; }
    bool IsActive() const { return m_active; }

    virtual void OnResize(int width, int height) = 0; 

    const std::wstring& GetName() const { return m_name; }

private:
    std::wstring                             m_name;
    bool                                     m_active = true;
    std::vector<std::unique_ptr<GameObject>> m_gameObjects;
};
