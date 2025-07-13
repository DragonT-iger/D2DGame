#include "pch.h"
#include "Game.h"

bool Game::Initialize()
{

	m_timer = std::make_unique<GameTimer>();

    m_timer->Reset();

	// 윈도우 초기화

	if (false == __super::Create(L"D2DEngineMK1", L"D2DEngineMK1", 1920, 1080))
	{
		return false;
	}
    



    // 맨 처음 씬 만들고 로드하는법
	SceneManager::Instance().Instance().Instance().Instance().Instance().RegisterScene(L"MainScene", std::make_unique<Scene>());

	SceneManager::Instance().LoadScene(L"MainScene"); // 이러면 awake랑 start 까지 초기화가 됨

	return true;
}

void Game::Run()
{
    MSG msg = { 0 };

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            //if (false == InputManager::Instance().OnHandleMessage(msg))
            //{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            //}
        }
        else
        {
            m_timer->Tick();
            Update(m_timer->DeltaTimeMS());
        }
    }
}

void Game::Update(float deltaTime)
{

	static float elapsedTime = 0.0f;
    static float fixedDeltaTime = 0.02f;
    
	elapsedTime += deltaTime;

    Scene* scene = SceneManager::Instance().GetActiveScene();
    if (scene && scene->IsActive())
    {
        while(elapsedTime >= fixedDeltaTime)
        {
            scene->FixedUpdate(fixedDeltaTime);
            elapsedTime -= fixedDeltaTime;
		}

        scene->Update(deltaTime);

		scene->LateUpdate(deltaTime);
	}
}

void Game::Release()
{
    m_timer = nullptr;
    __super::Destroy();
}

void Game::UpdateTime()
{
    assert(m_timer != nullptr && "타이머가 존재하지 않습니다!" );

    m_timer->Tick();
}

void Game::OnResize(int width, int height)
{
    __super::OnResize(width, height);
}

void Game::OnClose()
{
}
