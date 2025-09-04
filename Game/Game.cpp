#include "pch.h"
#include "Game.h"
#include "ExampleScene.h"
#include "MainScene.h"
#include "TitleScene.h"
#include "DTtestScene.h"
#include "ClientSceneManager.h"
#include "ArtTestView.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


bool Game::Initialize()
{
	m_timer = std::make_unique<GameTimer>();

    m_timer->Reset();

	// 윈도우 초기화

	if (false == __super::Create(L"D2DEngine", L"D2DEngine", 1920, 1080))
	{
		return false;
	}

    // 렌더러 초기화

	D2DRenderer::Instance().Initialize(static_cast<HWND>(GetHandle()));
    
    //리소스 매니저 세팅
    ResourceManager::Instance().SetResourcePath(std::filesystem::current_path() /"Assets");
    ResourceManager::Instance().LoadPath();

    //사운드 매니저 초기화
    SoundManager::Instance().Init();


    // 맨 처음 씬 만들고 로드하는법 수정됨 아래와 같이
    
    //ImGui 초기화
	ImGuiManager::Instance().Initialize(static_cast<HWND>(GetHandle()), D2DRenderer::Instance().GetD3DDevice(), D2DRenderer::Instance().GetD3DContext());


    // 아직 씬 포인터가 생성되기 전이라 Instantiate 못씀
    ClientSceneManager::Instance().LoadScene(std::make_unique<MainScene>());
    //SceneManager::Instance().LoadScene(L"ExampleScene");
    ClientSceneManager::Instance().LoadScene(std::make_unique<TitleScene>());
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

            const ImGuiIO& io = ImGui::GetIO();

            bool keyboardMsg = (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP);
            bool mouseMsg = (msg.message >= WM_MOUSEFIRST && msg.message <= WM_MOUSELAST);

            if ((keyboardMsg && (!io.WantCaptureKeyboard || msg.message == WM_KEYUP)) ||
                (mouseMsg && !io.WantCaptureMouse))
            {
                InputManager::Instance().OnHandleMessage(msg);
            }
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
    ClientSceneManager::Instance().ProcessSceneChange();

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
    assert(m_timer != nullptr && "타이머가 존재하지 않습니다!" );

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
        return true; // ImGui가 메시지를 처리했으면 true 반환
    }

    return false;
}

void Game::OnResize(int width, int height)
{
    __super::OnResize(width, height);
    /*Scene* scene = SceneManager::Instance().GetActiveScene();
    scene->OnResize(width , height);*/


    ImGuiManager::Instance().InvalidateDeviceObjects();
    D2DRenderer::Instance().Resize(width, height);

    ImGuiManager::Instance().CreateDeviceObjects();
}

void Game::OnClose()
{
	SceneManager::Instance().UnInitialize();
	ResourceManager::Instance().Uninitialize();
    D2DRenderer::Instance().Uninitialize();
}
