#pragma once

constexpr float EndTime = 183;
constexpr float StartStopTime = 3.0f; //게임 시작시 정지 시간

class Inventory;
struct SlotData;

class GameManager : public MonoBehaviour
{
public:
	GameManager() = default;
	static GameManager& Instance()
	{
		static GameManager inst;
		return inst;
	}

	//void Awake()                         override;
	//void Start()                         override;
	void Update(float deltaTime)         override;

	void Init();

	int ReceiveScore(const std::vector<SlotData>& data);

	int GetTotalScore() { return totalscore; }

	void AddScore(int num);

	enum class GameState
	{
		Title,
		Start,
		Tutorial,
		Pause,
		Main,
		Rage,
		End,
	};

	enum class EndReason
	{
		None,
		BabyStarved,
		PlayerDead,
		Happy
	};

	void OnInspectorGUI() override;

	void SetFullScreen(bool isFull);

	void LoadEndingScene(EndReason reason);

	void CheckHappyEnd();
	void CountThree();

	EndReason GetEndReason() { return m_endReason; }
	GameState GetGameState() { return  m_GameState; }
	void SetGameState(GameState state) { m_GameState = state; }

	void RegisterCountText(Text* text) { m_text = text; }
	void ResetTotalScore() { totalscore = 0; }
private:
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	static inline GameObject* m_player = nullptr;
	
	Inventory* m_inventory = nullptr;
	Text* m_text = nullptr;

	static int ep_count;
	static int pk_count;
	static int pt_count;
	static int totalscore;

	int countThree = 2;

	static inline GameState m_GameState = GameState::Start;
	static inline EndReason m_endReason = EndReason::None;

	bool m_isFullscreen = false;

	float inGameTime = 0.0f;
};
