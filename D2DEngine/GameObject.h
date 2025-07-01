#pragma once

class MonoBehaviour;

class GameObject
{
public:
    explicit GameObject(const wstring& name = L"GameObject");

    // ─────────────────────────────────────────────
    // MonoBehaviour
    // ─────────────────────────────────────────────
    template<typename T>
    T* AddComponent();

    template<typename T>
    T* GetComponent() const;

    // ─────────────────────────────────────────────
    // Activation
    // ─────────────────────────────────────────────
    void SetActive(bool active);
    bool IsActive() const;

    // ─────────────────────────────────────────────
    // Lifecycle dispatch
    // ─────────────────────────────────────────────
    void Awake();
    void Start();
    void FixedUpdate(float deltaTime); 
    void Update(float deltaTime);    
    void LateUpdate(float deltaTime);

private:
    wstring                           m_name;
    bool                              m_active = true;
    vector<unique_ptr<MonoBehaviour>> m_components;
};


template<typename T>
T* GameObject::AddComponent()
{
    // 런타임 타입 체크
    if (!is_base_of_v<MonoBehaviour, T>)
    {
        cout << "Error: T must derive from MonoBehaviour" << endl;
        assert(false && "T must derive from MonoBehaviour");
        return nullptr;
    }

    auto comp = make_unique<T>();
    T* raw = comp.get();
    m_components.emplace_back(move(comp));
    return raw;
}

template<typename T>
T* GameObject::GetComponent() const
{
    if (!is_base_of_v<MonoBehaviour, T>)
    {
        cout << "Error: T must derive from MonoBehaviour" << endl;
        assert(false && "T must derive from MonoBehaviour");
        return nullptr;
    }

    for (auto& c : m_components)
        if (auto casted = dynamic_cast<T*>(c.get()))
            return casted;
    return nullptr;
}