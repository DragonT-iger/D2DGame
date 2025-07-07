#pragma once

class MonoBehaviour;
/// 날짜 / 이름 / 수정내용
/// 2025-07-04 권용범 최초버전 작성

/// <summary>
/// Unity Like GameObject Class
/// </summary>
class GameObject
{
public:
    explicit GameObject(const wstring& name = L"GameObject");

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
};


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