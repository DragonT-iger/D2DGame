#pragma once

class MonoBehaviour;
class Transform;
/// 날짜 / 이름 / 수정내용
/// 2025-07-04 권용범 최초버전 작성
/// 2025-07-07 권용범 Transform 특수화

/// <summary>
/// Unity Like GameObject Class
/// </summary>
class GameObject
{
public:
    GameObject(const wstring& name = L"GameObject");

    template<typename T>
    T* AddComponent();

    template<typename T>
    T* GetComponent() const;

    void SetActive(bool active);
    bool IsActive() const;

private:
    wstring                           m_name;
    bool                              m_active = true;
    vector<unique_ptr<MonoBehaviour>> m_components;
    unique_ptr<Transform>             m_transform;
};




//템플릿은 cpp로 못옮겨

// 리턴 raw로 주니까 delete 절대하지마셈 나중에 shared_ptr 로 해도 되겠네 이거
template<typename T>
T* GameObject::AddComponent()
{
    static_assert(std::is_base_of_v<MonoBehaviour, T>, "T must derive from MonoBehaviour");
    // 컴파일 타임 타입 체크

    auto comp = make_unique<T>();
    T* raw = comp.get();
    m_components.emplace_back(move(comp));
    return raw;
}
template<>
Transform* GameObject::AddComponent<Transform>() {
    if (m_transform)
    {
        cwout << L"[GameObject] Transform already exists\n";
        assert(false && "Duplicate Transform on GameObject");
        return m_transform.get();
    }
    m_transform = make_unique<Transform>();
    return m_transform.get();
}

// 리턴 raw로 주니까 delete 절대하지마셈
template<typename T>
T* GameObject::GetComponent() const
{
    static_assert(std::is_base_of_v<MonoBehaviour, T>, "T must derive from MonoBehaviour");
    // 컴파일 타임 타입 체크

    for (auto& c : m_components)
        if (auto casted = dynamic_cast<T*>(c.get()))
            return casted;
    return nullptr;
}