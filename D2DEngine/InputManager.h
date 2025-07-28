#pragma once
#include <array>

/// ��¥ / �̸� / ��������
/// 2025-07-09 ���ʹ��� �ۼ���
/// 
/// <summary>
/// �������� ������� �� InputManager 
/// <summary>



struct MouseState
{
	POINT pos{ 0, 0 };// ���콺 ������

	bool LButtonPressed{ false };	// ���콺 ���� ��ư ���� ����
	bool RButtonPressed{ false };	// ���콺 ������ ��ư ���� ����
	int  wheelDelta{ 0 };
	bool wheelUp{ false };			// ���콺 �� ���� ��ũ��
	bool wheelDown{ false };		// ���콺 �� �Ʒ��� ��ũ��
};

struct KeyEdge
{
	bool pressed{ false };	// ���� ����	
	bool released{ false };	// ��� ����	
};

class InputManager	//�̱������� ������
{
	InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
public:
	virtual ~InputManager() = default;

	static InputManager& Instance()
	{
		static InputManager instance;

		return instance;
	}

	bool Init(HWND hwnd);

	void EndFrame();

	bool OnHandleMessage(const MSG& msg);

	bool GetKeyPressed(Keycode vk);

	bool GetKeyDown(Keycode vk);

	MouseState GetMouseState() const { return m_CurMouse; }

	int  GetWheelDelta()      const { return m_CurMouse.wheelDelta; } 
	bool GetWheelUp()         const { return m_CurMouse.wheelUp; }
	bool GetWheelDown()       const { return m_CurMouse.wheelDown; }

private:

	void HandleMsgKeyDown(WPARAM wParam, LPARAM lParam);

	void HandleMsgKeyUp(WPARAM wParam, LPARAM lParam);

	void HandleMsgMouse(const MSG& msg);

	MouseState m_CurMouse;	// ���� ���콺 ����

	std::array<bool, 256> m_keyDown;	// ���� Down ����
	std::array<KeyEdge, 256> m_keyEdge;	// �̹� ������ Edge ���
};

inline int GetXFromLParam(LPARAM lp) { return (int)(short)(LOWORD(lp)); }
inline int GetYFromLParam(LPARAM lp) { return (int)(short)(HIWORD(lp)); }

inline InputManager& Input = InputManager::Instance();