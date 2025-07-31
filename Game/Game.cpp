#include "pch.h"
#include "Game.h"
#include "ExampleScene.h"
#include "HSTestScene.h"
#include "MainScene.h"

#ifdef _DEBUG
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

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
    ResourceManager::Instance().SetResourcePath(std::filesystem::current_path() / "Assets");
    ResourceManager::Instance().LoadPath();


    // �� ó�� �� ����� �ε��ϴ¹�
    SceneManager::Instance().Instance().Instance().Instance().Instance().RegisterScene(L"ExampleScene", std::make_unique<ExampleScene>());
	SceneManager::Instance().Instance().Instance().Instance().Instance().RegisterScene(L"MainScene", std::make_unique<MainScene>());
	SceneManager::Instance().Instance().Instance().Instance().Instance().RegisterScene(L"HSTestScene", std::make_unique<HSTestScene>());

    
    //ImGui �ʱ�ȭ
#ifdef _DEBUG
	ImGuiManager::Instance().Initialize(static_cast<HWND>(GetHandle()), D2DRenderer::Instance().GetD3DDevice(), D2DRenderer::Instance().GetD3DContext());


#endif

    // ���� �� �����Ͱ� �����Ǳ� ���̶� Instantiate ����

    //SceneManager::Instance().LoadScene(L"MainScene");
    //SceneManager::Instance().LoadScene(L"ExampleScene");
     SceneManager::Instance().LoadScene(L"HSTestScene");

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

	static float elapsedTime = 0.0f;
    static float fixedDeltaTime = 0.02f;
    
	elapsedTime += deltaTime;

    Scene* scene = SceneManager::Instance().GetActiveScene();


	D2DRenderer::Instance().RenderBegin();

#ifdef _DEBUG
    ImGuiManager::Instance().BeginFrame(deltaTime);
#endif // _DEBUG



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

#ifdef _DEBUG
    ImGuiManager::Instance().EndFrame(D2DRenderer::Instance().GetD3DRenderTargetView());
#endif

    D2DRenderer::Instance().Present();
}

void Game::Release()
{
    m_timer = nullptr;
#ifdef _DEBUG
	ImGuiManager::Instance().Shutdown();
#endif
    
    __super::Destroy();
}

void Game::UpdateTime()
{
    assert(m_timer != nullptr && "Ÿ�̸Ӱ� �������� �ʽ��ϴ�!" );

    m_timer->Tick();
}

bool Game::OnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef _DEBUG
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
    {
        return true; // ImGui�� �޽����� ó�������� true ��ȯ
    }
#endif
    InputManager::Instance().OnHandleMessage({ hwnd, msg , wParam, lParam, 0 , {0, 0} });

    return false;
}

void Game::OnResize(int width, int height)
{
    __super::OnResize(width, height);
    /*Scene* scene = SceneManager::Instance().GetActiveScene();
    scene->OnResize(width , height);*/
}

void Game::OnClose()
{
	SceneManager::Instance().UnInitialize();
	ResourceManager::Instance().Uninitialize();
    D2DRenderer::Instance().Uninitialize();
}
