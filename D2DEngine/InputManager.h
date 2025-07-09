#pragma once
/// 날짜 / 이름 / 수정내용
/// 2025-07-09 최초버전 작성중
/// 
/// <summary>
/// 엔진에서 기반으로 쓸 InputManager 
/// <summary>

enum class Keycode
{
	// 키보드 키코드 정의

	//방향키, 스페이스바
	SPACE =		0x20,
	LEFT=			0x25,
	UP =			0x26,
	RIGHT =		0x27,
	DOWN  =	0x28,

	//알파벳
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
	POINT pos{ 0, 0 };// 마우스 포지션

	bool LButtionPressed{ false };	// 마우스 왼쪽 버튼 눌림 상태
	bool RButtionPressed{ false };	// 마우스 오른쪽 버튼 눌림 상태
};

struct KeyEdge
{
	bool pressed{ false };	// 눌림 상태	
	bool released{ false };	// 평소 상태	
};

class InputManager	//싱글톤으로 쓸거임
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

	MouseState m_CurMouse;	// 현재 마우스 상태

	bool m_keyDown[256] = {};   // 현재 Down 상태
	KeyEdge m_keyEdge[256] = {};   // 이번 프레임 Edge 결과
};

int GetXFromLParam(LPARAM lp) { return (int)(short)(LOWORD(lp)); }
int GetYFromLParam(LPARAM lp) { return (int)(short)(HIWORD(lp)); }