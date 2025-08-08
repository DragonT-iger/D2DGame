#include "pch.h"
#include "InputManager.h"
#include <array>



bool InputManager::Init(HWND hwnd)
{
	
	return true;
}

void InputManager::EndFrame()
{
	//std::fill(m_keyEdge.begin(), m_keyEdge.end(), KeyEdge{});

	// 이번 프레임 휠 플래그/델타 초기화
	m_CurMouse.wheelUp = false;
	m_CurMouse.wheelDown = false;
	m_CurMouse.wheelDelta = 0;
}

bool InputManager::OnHandleMessage(const MSG& msg)
{
	switch (msg.message)// wParam에 누른 키정보, lParam에 누른 키 상태 정보가 들어있음 
	{
	case WM_KEYDOWN:
	{
		HandleMsgKeyDown(msg.wParam, msg.lParam);
	}
	break;

	case WM_KEYUP:
	{
		HandleMsgKeyUp(msg.wParam, msg.lParam);
	}
	break;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	{
		HandleMsgMouse(msg);
	}
	break;


	default:
		return false; // Unhandled message
	}

	return true;
}

bool InputManager::GetKeyPressed(Keycode vk)
{
	bool p = m_keyEdge[static_cast<UINT>(vk)].pressed;

	m_keyEdge[static_cast<UINT>(vk)].pressed = false;	//때는 타이밍에 false인데 교수님 코드는 여기서 안하고 GetKeyPressed에서 처리했었음 뭐가 다른가?

	return p;
}

bool InputManager::GetKeyDown(Keycode vk)
{
	return m_keyDown[static_cast<UINT>(vk)];
}

int InputManager::GetAxisRaw(const std::string& axis)
{
	if (axis == "Vertical")
	{
		//bool up = m_keyDown[static_cast<UINT>(Keycode::UP)] || m_keyDown[static_cast<UINT>(Keycode::W)];
		//bool down = m_keyDown[static_cast<UINT>(Keycode::DOWN)] || m_keyDown[static_cast<UINT>(Keycode::S)];

		bool up = m_keyDown[static_cast<UINT>(Keycode::UP)];
		bool down = m_keyDown[static_cast<UINT>(Keycode::DOWN)];

		if (up && !down) return 1;
		if (!up && down) return -1;
		return 0; 
	}
	else if (axis == "Horizontal")
	{
		//bool right = m_keyDown[static_cast<UINT>(Keycode::RIGHT)] || m_keyDown[static_cast<UINT>(Keycode::D)];
		//bool left = m_keyDown[static_cast<UINT>(Keycode::LEFT)] || m_keyDown[static_cast<UINT>(Keycode::A)];

		bool right = m_keyDown[static_cast<UINT>(Keycode::RIGHT)];
		bool left = m_keyDown[static_cast<UINT>(Keycode::LEFT)];

		if (right && !left) return 1;
		if (!right && left) return -1;
		return 0; 
	}

	return 0;
}

void InputManager::HandleMsgKeyDown(WPARAM wParam, LPARAM lParam)
{
	assert(wParam < 256); //wParam은 0~255 사이의 값이 들어옴

	bool wasPressed = (lParam & (1 << 30)) != 0; // lParam의 30번째 비트가 눌린 상태인지 여부를 나타냄

	m_keyDown[wParam] = true;

	if (!wasPressed)
	{
		m_keyEdge[wParam].pressed = true; // 처음 눌렸을 때만 true
	}

	m_keyEdge[wParam].released = false; //눌렸으니까 false
}

void InputManager::HandleMsgKeyUp(WPARAM wParam, LPARAM lParam)
{
	assert(wParam < 256); //wParam은 0~255 사이의 값이 들어옴

	m_keyDown[wParam] = false;
	m_keyEdge[wParam].released = true;
}

void InputManager::HandleMsgMouse(const MSG& msg)
{
	int x = GetXFromLParam(msg.lParam);
	int y = GetYFromLParam(msg.lParam);

	m_CurMouse.pos = { x, y };

	if (msg.message == WM_LBUTTONDOWN)
	{
		m_CurMouse.LButtonPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_RBUTTONDOWN)
	{
		m_CurMouse.RButtonPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_LBUTTONUP)
	{
		m_CurMouse.LButtonPressed = false;
		ReleaseCapture();
	}
	else if (msg.message == WM_MBUTTONDOWN) 
	{
		m_CurMouse.MButtonPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_MBUTTONUP)
    {
        m_CurMouse.MButtonPressed = false;
        ReleaseCapture();
    }
	else if (msg.message == WM_RBUTTONUP)
	{
		m_CurMouse.RButtonPressed = false;
		ReleaseCapture();
	}
	else if(msg.message == WM_MOUSEWHEEL)
	{
		int delta = GET_WHEEL_DELTA_WPARAM(msg.wParam);
		m_CurMouse.wheelDelta = delta;
		m_CurMouse.wheelUp |= (delta > 0);
		m_CurMouse.wheelDown |= (delta < 0);

		//cwout << "Wheel Delta: " << m_CurMouse.wheelDelta << std::endl;
	}
}
