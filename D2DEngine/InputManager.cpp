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

	// �̹� ������ �� �÷���/��Ÿ �ʱ�ȭ
	m_CurMouse.wheelUp = false;
	m_CurMouse.wheelDown = false;
	m_CurMouse.wheelDelta = 0;
}

bool InputManager::OnHandleMessage(const MSG& msg)
{
	switch (msg.message)// wParam�� ���� Ű����, lParam�� ���� Ű ���� ������ ������� 
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

	m_keyEdge[static_cast<UINT>(vk)].pressed = false;	//���� Ÿ�ֿ̹� false�ε� ������ �ڵ�� ���⼭ ���ϰ� GetKeyPressed���� ó���߾��� ���� �ٸ���?

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
	assert(wParam < 256); //wParam�� 0~255 ������ ���� ����

	bool wasPressed = (lParam & (1 << 30)) != 0; // lParam�� 30��° ��Ʈ�� ���� �������� ���θ� ��Ÿ��

	m_keyDown[wParam] = true;

	if (!wasPressed)
	{
		m_keyEdge[wParam].pressed = true; // ó�� ������ ���� true
	}

	m_keyEdge[wParam].released = false; //�������ϱ� false
}

void InputManager::HandleMsgKeyUp(WPARAM wParam, LPARAM lParam)
{
	assert(wParam < 256); //wParam�� 0~255 ������ ���� ����

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
