#include "pch.h"
#include "ImGuiWindow.h"
#ifdef _DEBUG
void ImGuiWindow::Draw(float)
{
    DrawHierarchy();
    DrawInspector();
}

void ImGuiWindow::DrawHierarchy()
{
    auto* scene = SceneManager::Instance().GetActiveScene();
    if (!scene) return;

    ImGui::Begin("Hierarchy");
    for (auto& goPtr : scene->GetGameObjects())
    {
        GameObject* go = goPtr.get();
        bool selected = (go == m_selected);
        if (ImGui::Selectable(go->GetName().c_str(), selected))
            m_selected = go;
    }
    ImGui::End();
}

void ImGuiWindow::DrawInspector()
{
    if (!m_selected) return;

    ImGui::Begin("Inspector");

    // ���� �̸� & Active ����

    static char nameBuf[128];

    strncpy_s(nameBuf, m_selected->GetName().c_str(), sizeof(nameBuf));

    if (ImGui::InputText("Name", nameBuf, IM_ARRAYSIZE(nameBuf)))
        m_selected->SetName(std::string(nameBuf));

    bool active = m_selected->IsActive();
    if (ImGui::Checkbox("Active", &active))
        m_selected->SetActive(active);

    ImGui::Separator();

    // ���� Transform ����
    if (Transform* tr = m_selected->GetComponent<Transform>())
    {
        Vector2 pos = tr->GetPosition();
        float rot  = tr->GetRotation();
        Vector2 scl = tr->GetScale();

        if (ImGui::DragFloat2("Position", &pos.x, 0.1f))
            tr->SetPosition(pos);
        if (ImGui::DragFloat("Rotation", &rot, 1.0f))
            tr->SetRotation(rot);
        if (ImGui::DragFloat2("Scale", &scl.x, 0.01f))
            tr->SetScale(scl);
    }

    ImGui::Separator();

    // ���� ������Ʈ ����Ʈ & Behaviour ��� ����
    ImGui::Text("Components:");
    for (const auto& c : m_selected->GetComponents())
    {
        const char* typeName = typeid(*c).name();
        if (auto* beh = dynamic_cast<Behaviour*>(c.get()))
        {
            bool enabled = beh->IsEnabled();        // Behaviour ���� on/off ���� ���
            ImGui::Checkbox(typeName, &enabled);
            if (ImGui::IsItemEdited())
                beh->SetEnabled(enabled);
        }
        else
        {
            ImGui::TextUnformatted(typeName);
        }
    }

    ImGui::End();
}

#endif