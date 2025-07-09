#pragma once
/// ��¥ / �̸� / ��������
/// 2025-07-09 ���ʹ��� �ۼ���
/// 
/// <summary>
/// �������� ������� �� InputManager 
/// <summary>

enum class Keycode
{
	// Ű���� Ű�ڵ� ����

	//����Ű, �����̽���
	SPACE =		0x20,
	LEFT=			0x25,
	UP =			0x26,
	RIGHT =		0x27,
	DOWN  =	0x28,

	//���ĺ�
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	
};

struct MouseState
{
	POINT pos{ 0, 0 };// ���콺 ������

	bool LButtionPressed{ false };	// ���콺 ���� ��ư ���� ����
	bool RButtionPressed{ false };	// ���콺 ������ ��ư ���� ����
};

struct KeyEdge
{
	bool pressed{ false };	// ���� ����	
	bool released{ false };	// ��� ����	
};

class InputManager	//�̱������� ������
{
	InputManager() = default;
	virtual ~InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
public:
	static InputManager& Instance()
	{
		static InputManager instance;

		return instance;
	}

	bool Init(HWND hwnd);

	bool OnHandleMessage(const MSG& msg);

	bool GetKeyPressed(UINT vk);

	bool GetKeyDown(UINT vk);

	MouseState GetMouseState() const { return m_CurMouse; }

private:

	void HandleMsgKeyDown(WPARAM wParam, LPARAM lParam);

	void HandleMsgKeyUp(WPARAM wParam, LPARAM lParam);

	void HandleMsgMouse(const MSG& msg);

	MouseState m_CurMouse;	// ���� ���콺 ����

	bool m_keyDown[256] = {};   // ���� Down ����
	KeyEdge m_keyEdge[256] = {};   // �̹� ������ Edge ���
};

int GetXFromLParam(LPARAM lp) { return (int)(short)(LOWORD(lp)); }
int GetYFromLParam(LPARAM lp) { return (int)(short)(HIWORD(lp)); }