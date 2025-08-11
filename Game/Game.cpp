#include "pch.h"
#include "Game.h"
#include "ExampleScene.h"
#include "MainScene.h"
#include "TestTitleScene.h"
#include "DTtestScene.h"
#include "ArtTestView.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


bool Game::Initialize()
{
	m_timer = std::make_unique<GameTimer>();

    m_timer->Reset();

	// ������ �ʱ�ȭ

	if (false == __super::Create(L"D2DEngine", L"D2DEngine", 1920, 1080))
	{
		return false;
	}

    // ������ �ʱ�ȭ

	D2DRenderer::Instance().Initialize(static_cast<HWND>(GetHandle()));
    
    //���ҽ� �Ŵ��� ����
    ResourceManager::Instance().SetResourcePath(std::filesystem::current_path() /"Assets");
    ResourceManager::Instance().LoadPath();

    //���� �Ŵ��� �ʱ�ȭ
    SoundManager::Instance().Init();


    // �� ó�� �� ����� �ε��ϴ¹� ������ �Ʒ��� ����
    
    //ImGui �ʱ�ȭ
	ImGuiManager::Instance().Initialize(static_cast<HWND>(GetHandle()), D2DRenderer::Instance().GetD3DDevice(), D2DRenderer::Instance().GetD3DContext());


    // ���� �� �����Ͱ� �����Ǳ� ���̶� Instantiate ����
    SceneManager::Instance().LoadScene(std::make_unique<MainScene>());
    //SceneManager::Instance().LoadScene(L"ExampleScene");
    SceneManager::Instance().LoadScene(std::make_unique<TitleScene>());
    //SceneManager::Instance().LoadScene(L"DTtestScene");

    //D2DRenderer::Instance().SetFullscreen(true);

    
	return true;
}

void Game::Run()
{
    MSG msg = { 0 };

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            m_timer->Tick();
            LifeCycle(m_timer->DeltaTime()); 
        }
    }
}

void Game::LifeCycle(float deltaTime)
{
    SceneManager::Instance().ProcessSceneChange();

	static float elapsedTime = 0.0f;
    static float fixedDeltaTime = 0.02f;
    
	elapsedTime += deltaTime;

    Scene* scene = SceneManager::Instance().GetActiveScene();


	D2DRenderer::Instance().RenderBegin();

    ImGuiManager::Instance().BeginFrame(deltaTime);



    if (scene && scene->IsActive())
    {
        while(elapsedTime >= fixedDeltaTime)
        {
            scene->FixedUpdate(fixedDeltaTime);
            elapsedTime -= fixedDeltaTime;
		}

        scene->Update(deltaTime);

		scene->LateUpdate(deltaTime);

        scene->Render();
	}

    InputManager::Instance().EndFrame();

    D2DRenderer::Instance().RenderEnd(false);

    ImGuiManager::Instance().EndFrame(D2DRenderer::Instance().GetD3DRenderTargetView());

    D2DRenderer::Instance().Present();
}

void Game::Release()
{
    m_timer = nullptr;
	ImGuiManager::Instance().Shutdown();
    
    __super::Destroy();
}

void Game::UpdateTime()
{
    assert(m_timer != nullptr && "Ÿ�̸Ӱ� �������� �ʽ��ϴ�!" );

    m_timer->Tick();
}

bool Game::OnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

    if (msg == WM_SYSKEYDOWN && wParam == VK_RETURN && (lParam & (1 << 29)))
    {
        return true;
    }


    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
    {
        return true; // ImGui�� �޽����� ó�������� true ��ȯ
    }
    InputManager::Instance().OnHandleMessage({ hwnd, msg , wParam, lParam, 0 , {0, 0} });

    return false;
}

void Game::OnResize(int width, int height)
{
    __super::OnResize(width, height);
    /*Scene* scene = SceneManager::Instance().GetActiveScene();
    scene->OnResize(width , height);*/

    D2DRenderer::Instance().Resize(width, height);
    ImGuiManager::Instance().OnResize();
}

void Game::OnClose()
{
	SceneManager::Instance().UnInitialize();
	ResourceManager::Instance().Uninitialize();
    D2DRenderer::Instance().Uninitialize();
}
