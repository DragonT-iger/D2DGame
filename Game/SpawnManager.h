#pragma once
#include <random>

class SpawnManager : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

	void DestroyObject(GameObject* obj);
	
	using Random = std::uniform_int_distribution<int>;

private:
	bool IsInnerRect(const RECT& rect, const int& x, const int& y);
	bool CheckRange(const Vector2& pos, FarmRank rank);

	GameObject* CreateNewCrop(FarmRank rank);

	Vector2 CreateSpawnPoint(const RECT& outRect, const RECT& inRect, FarmRank rank);
	Crops SetCropType();

	void SetCropData(Crop* obj, Crops type, FarmRank rank);

	float			m_spawnTimeA;
	float			m_elapsedTimeA;
	float			m_spawnTimeB;
	float			m_elapsedTimeB;
	float			m_spawnTimeC;
	float			m_elapsedTimeC;

	float			m_spawnRange = 200.f;

	RECT						   farm_A;
	RECT						   farm_B;
	RECT						   farm_C;
	RECT							 Home;

	Scene* curScene;

	int		m_maxRate_A;
	int		m_maxRate_B;
	int		m_maxRate_C;

	std::list<GameObject*> m_farmAList;
	std::list<GameObject*> m_farmBList;
	std::list<GameObject*> m_farmCList;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_pumpkinSprite;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_eggplantSprite;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_potatoSprite;

	std::mt19937 gen;
};
