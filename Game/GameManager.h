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
	//void Update(float deltaTime)         override;

	void Init();

	int ReceiveScore(const std::vector<SlotData>& data);

	int GetTotalScore() { return totalscore; }

	enum class EndReason
	{
		None,
		BabyStarved,
		PlayerStarved,
		Win
	};


	void LoadEndingScene(EndReason reason);
	EndReason GetEndReason() { return m_endReason; }
	// 슬라이더 value 없음? 그걸로 연동하는데 보통

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
	static int totalscore;

	EndReason m_endReason = EndReason::None;
};
