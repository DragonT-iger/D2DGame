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
            //Update(m_timer->DeltaTimeMS());
        }
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
