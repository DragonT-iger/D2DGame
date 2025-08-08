#pragma once

class Crop;
enum Crops;
enum FarmRank;

struct GrowSpeed {
	float growSpeedS;
	float growSpeedM;
	float growSpeedL;
};

class SpawnManager : public MonoBehaviour
{
public:
	void Awake() override;
	void Update(float deltaTime) override;

	void DestroyObject(GameObject* obj);

	GrowSpeed& GetGrowSpeed(FarmRank rank);

private:

#ifdef _DEBUG
	void OnInspectorGUI() override;

	void DestroyAllCrop();
#endif // _DEBUG

	bool IsInnerRect(const RECT& rect, const int& x, const int& y);
	bool CheckRange(const Vector2& pos, FarmRank rank);

	GameObject* CreateNewCrop(FarmRank rank);

	Vector2 CreateSpawnPoint(const RECT& outRect, const RECT& inRect, FarmRank rank);
	Crops SetCropType(FarmRank rank);
	Crops RandomCrop(UINT epProb, UINT ptProb, UINT pkProp);

	void SetCropData(Crop* obj, Crops type, FarmRank rank, GameObject* eftObj);

	GrowSpeed rankA = { 3, 4, 7 };
	GrowSpeed rankB = { 5, 7, 10 };
	GrowSpeed rankC = { 8, 12, 0 };

	std::vector<GrowSpeed*> growArr;

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

	std::shared_ptr<AnimationClip> m_effectSprite;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_pumpkinSprite;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_eggplantSprite;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_potatoSprite;

	std::unordered_map<Crops, std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>*> m_cropSprites;

	Scene* curScene;
};
