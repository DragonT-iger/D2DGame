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

	struct FarmData {
		FarmRank rank;
		int maxRate;
		float elapsedTime;
		float spawnTime;
		std::vector<GameObject*>* farmlist;
	};

	std::vector<FarmData> farmArr;

	std::vector<GameObject*> m_farmAList;
	std::vector<GameObject*> m_farmBList;
	std::vector<GameObject*> m_farmCList;

	float			m_spawnRange = 200.f;

	RECT						   farm_A;
	RECT						   farm_B;
	RECT						   farm_C;
	RECT							 Home;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_pumpkinSprite;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_eggplantSprite;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_potatoSprite;

	std::mt19937 gen;
	Scene* curScene;
};
