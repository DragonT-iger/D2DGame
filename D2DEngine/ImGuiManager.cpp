
#include "pch.h"
#include "ImGuiManager.h"
#include "ImGuiWindow.h"
#ifdef _DEBUG
ImGuiManager& ImGuiManager::Instance()
{
    static ImGuiManager instance;
    return instance;
}

void ImGuiManager::Initialize(HWND hwnd,
    ID3D11Device* device,
    ID3D11DeviceContext* context)
{
    if (m_initialized) return;

    m_hwnd = hwnd;
    m_device = device;
    m_context = context;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // 도킹 없음

    ImGui_ImplWin32_Init(m_hwnd);
    ImGui_ImplDX11_Init(m_device, m_context);

    m_initialized = true;
}

void ImGuiManager::Show(float deltaTime)
{
    static bool show_demo = true;
    ImGui::ShowDemoWindow(&show_demo);
}

void ImGuiManager::BeginFrame(float deltaTime)
{
    assert(m_initialized && "ImGuiManager not initialized!");
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    m_imGuiWindow->Draw(deltaTime);
}

void ImGuiManager::EndFrame(ID3D11RenderTargetView* mainRTV)
{
    assert(m_initialized && "ImGuiManager not initialized!");

    ID3D11RenderTargetView* rtvs[1] = { mainRTV };
    m_context->OMSetRenderTargets(1, rtvs, nullptr);

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Shutdown()
{
    if (!m_initialized) return;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    m_initialized = false;
}
#endif