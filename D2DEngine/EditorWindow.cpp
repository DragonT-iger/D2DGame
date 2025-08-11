#include "pch.h"
#include "EditorWindow.h"
#include "../Game/TitleScene.h";
#include "../Game/MainScene.h"
#include "../Game/EndingScene.h"
//#include "../Game/

void EditorWindow::Draw(float deltaTime)
{
    if (SceneManager::Instance().GetDebugMode() == false) {
        return;
    }
    DrawDebug();
    DrawHierarchy();
    DrawInspector();
}

void EditorWindow::DrawDebug() {
    static bool m_showGrid = false;
    if (ImGui::Checkbox("Show Grid", &m_showGrid)) {
        Scene* curScene = SceneManager::Instance().GetActiveScene();
        curScene->SetGridOn(m_showGrid);
    }

    static const char* kSceneNames[] = { "TitleScene", "MainScene", "EndingScene" };
    static constexpr int kSceneCount = sizeof(kSceneNames) / sizeof(kSceneNames[0]);

    static int selected = 0;
    ImGui::Combo("Scene", &selected, kSceneNames, kSceneCount);

    ImGui::SameLine();
    if (ImGui::Button("Load"))
    {
        // 선택된 이름에 따라 실제 씬 객체 생성 → 고유포인터로 넘김
        std::unique_ptr<Scene> newScene;

        switch (selected)
        {
            case 0: newScene = std::make_unique<TitleScene>();   break;
            case 1: newScene = std::make_unique<MainScene>();      break;
            case 2: newScene = std::make_unique<EndingScene>();  break;
            default: assert(false && "Invalid scene index");     return;
        }

        SceneManager::Instance().LoadScene(std::move(newScene));

        m_selected = nullptr;        // Hierarchy 선택 리셋
        m_componentOpen.clear();     // Inspector 폴드 상태 리셋
    }
}

void EditorWindow::DrawHierarchy()
{
    auto* scene = SceneManager::Instance().GetActiveScene();
    if (!scene) return;

    ImGui::Begin("Hierarchy");
    for (auto& goPtr : scene->GetGameObjects())
    {
        GameObject* go = goPtr.get();
        ImGui::PushID(go);
        bool selected = (go == m_selected);
        if (ImGui::Selectable(go->GetName().c_str(), selected))
            m_selected = go;
        ImGui::PopID();
    }
    
    ImGui::End();
}

void EditorWindow::DrawInspector()
{
    if (!m_selected) return;

    ImGui::Begin("Inspector");

    // ── 이름 & Active ──

    static char buf[128];

    strncpy_s(buf, m_selected->GetName().c_str(), sizeof(buf));

    if (ImGui::InputText("Name", buf, IM_ARRAYSIZE(buf)))
        m_selected->SetName(std::string(buf));


    strncpy_s(buf, m_selected->GetTag().c_str(), sizeof(buf));

    if (ImGui::InputText("Tag", buf, IM_ARRAYSIZE(buf)))
        m_selected->SetTag(std::string(buf));


    bool active = m_selected->IsActive();
    if (ImGui::Checkbox("Active", &active))
        m_selected->SetActive(active);

    ImGui::Separator();

    // ── Transform ──
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

    ImGui::Text("Components:");

    for (const auto& c : m_selected->GetComponents())
    {
        ImGui::PushID(c.get());
        const char* typeName = typeid(*c).name();

        Behaviour* beh = dynamic_cast<Behaviour*>(c.get());
        bool enabled = beh ? beh->IsActive() : true;

        if (ImGui::Checkbox("##Enabled", &enabled) && beh)
            beh->SetActive(enabled);

        ImGui::SameLine();

        ImGui::TextUnformatted(typeName);
        ImGui::SameLine();

        bool& open = m_componentOpen.try_emplace(c.get(), true).first->second;

        ImGui::SameLine(ImGui::GetCursorPosX()
            + ImGui::GetContentRegionAvail().x
            - ImGui::GetFrameHeight());  

        if (ImGui::SmallButton(open ? "-##toggle" : "+##toggle"))
            m_componentOpen[c.get()] = !open;

        ImGui::PopID();

        if (open)
        {
            ImGui::Indent();
            auto* go = c.get();
            ImGui::PushID(go);
            c->OnInspectorGUI();
            ImGui::PopID();
            ImGui::Unindent();
        }
    }

    ImGui::End();
}