#pragma once
class Inventory;
struct SlotData;

enum class GameState
{
	Start,
	Pause,
	Rage,
	End,
};

class GameManager : public MonoBehaviour
{
public:
	static GameManager& Instance()
	{
		static GameManager inst;
		return inst;
	}

	//void Awake()                         override;
	//void Start()                         override;
	void Update(float deltaTime)         override;

	void Init();
	GameState GetGameState() { return m_GameState; }
	void SetGameState(GameState s) { m_GameState = s; }

	int ReceiveScore(const std::vector<SlotData>& data);

private:
	GameManager() = default;
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	GameObject* m_player = nullptr;

	GameState m_GameState = GameState::Start;

	Inventory* m_inventory = nullptr;

	static int ep_count;
	static int pk_count;
	static int pt_count;
	static int score;
};
