#pragma once
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
		Start,
		Tutorial,
		Pause,
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
	EndReason GetEndReason() { return m_endReason; }


private:
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
	static int totalscore;

	static inline EndReason m_endReason = EndReason::None;

	bool m_isFullscreen = false;
};
