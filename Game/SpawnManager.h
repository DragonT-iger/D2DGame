#pragma once

class SpawnManager : public MonoBehaviour
{
public:
	void Awake() override;
	void Update(float deltaTime) override;

	void DestroyObject(GameObject* obj);

private:
	bool IsInnerRect(const RECT& rect, const int& x, const int& y);
	bool CheckRange(const Vector2& pos, FarmRank rank);

	GameObject* CreateNewCrop(FarmRank rank);

	Vector2 CreateSpawnPoint(const RECT& outRect, const RECT& inRect, FarmRank rank);
	Crops SetCropType(FarmRank rank);

	void SetCropData(Crop* obj, Crops type, FarmRank rank, GameObject* msg);

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

	Scene* curScene;
};
