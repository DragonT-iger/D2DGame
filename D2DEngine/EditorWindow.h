#pragma once
#ifdef _DEBUG
// 하이라키 창과 Inspector 창을 만들꺼임
class EditorWindow
{
public:
    void Draw(float deltaTime);   // BeginFrame 에서 호출

private:
    void DrawHierarchy();
    void DrawInspector();

    GameObject* m_selected = nullptr;   // 현재 선택된 오브젝트
    std::unordered_map<const Component*, bool> m_componentOpen;
};

#endif