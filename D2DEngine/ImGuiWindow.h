#pragma once
#ifdef _DEBUG
// ���̶�Ű â�� Inspector â�� ���鲨��
class ImGuiWindow
{
public:
    void Draw(float deltaTime = 0.f);   // BeginFrame ���� ȣ��

private:
    void DrawHierarchy();
    void DrawInspector();

    GameObject* m_selected = nullptr;   // ���� ���õ� ������Ʈ
};

#endif