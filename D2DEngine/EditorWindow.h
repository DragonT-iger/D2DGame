#pragma once
// ���̶�Ű â�� Inspector â�� ���鲨��
class EditorWindow
{
public:
    void Draw(float deltaTime);   // BeginFrame ���� ȣ��

private:
    void DrawDebug();
    void DrawHierarchy();
    void DrawInspector();

    GameObject* m_selected = nullptr;   // ���� ���õ� ������Ʈ
    std::unordered_map<const Component*, bool> m_componentOpen;
};