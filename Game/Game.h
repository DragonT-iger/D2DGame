#pragma once
class Game : public NzWndBase
{
public:
	Game() = default;
	virtual ~Game() = default;

	bool Initialize();// NzWndBase �ʱ�ȭ , Renderer �ʱ�ȭ
	void Run();
	void Release();

private:
	void LifeCycle(float deltaTime);
	void UpdateTime();

	// ������ ���ν��� ������

	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) override;

	void OnResize(int width, int height) override;
	void OnClose() override;

	std::unique_ptr<GameTimer> m_timer;
};

