#pragma once
#ifdef _DEBUG
class ImGuiWindow;
class ImGuiManager
{
public:                  
    static ImGuiManager& Instance();

    void Initialize(HWND hwnd,
        ID3D11Device* device,
        ID3D11DeviceContext* context);

    void Show(float deltaTime);

    void BeginFrame(float deltaTime);
    void EndFrame(ID3D11RenderTargetView* mainRTV);

    void Shutdown();

private:
    ImGuiManager() = default;
    ~ImGuiManager() = default;
    ImGuiManager(const ImGuiManager&) = delete;
    ImGuiManager& operator=(const ImGuiManager&) = delete;

private:
    bool                 m_initialized{ false };
    HWND                 m_hwnd{ nullptr };
    ID3D11Device*        m_device{ nullptr };
    ID3D11DeviceContext* m_context{ nullptr };

    std::unique_ptr<ImGuiWindow> m_imGuiWindow = std::make_unique<ImGuiWindow>();
};
#endif