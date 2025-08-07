#pragma once

enum Crops {
	Eggplant = 0,
	Potato = 1,
	Pumpkin = 2,
	Nothing
};

enum Size {
	Born = 0,
	S = 1,
	M = 2,
	L = 3,
};

enum FarmRank
{
	Rank_A = 0,
	Rank_B = 1,
	Rank_C = 2,
};

class SpawnManager;

class Crop : public MonoBehaviour
{
public:

	void Awake()		  override;
	void Update(float dt) override;

	Size GetSize() { return m_size; }
	Crops	GetCropType() { return m_type; }

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerExit(Collider* other) override;
	FarmRank GetFarmRank() { return m_rank; }

	//void SetCropData(FarmRank rank, Crops type, std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> gameSprites, std::shared_ptr<AnimationClip> clip = nullptr, GameObject* msg);
	void SetCropData(FarmRank rank, Crops type, std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> gameSprites, GameObject* eftobj = nullptr);

	void Destroy();
protected:
	float m_growSpeed_S;
	float m_growSpeed_M;
	float m_growSpeed_L;
	float m_elapsedTime = 0.0f;
	Size m_size = Size::Born;
	Size m_maxSize;
	Crops	m_type;

	FarmRank m_rank;

	bool isSpawn = false;

	SpriteRenderer* m_SpriteRenderer;
	Animator* m_Animator;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_GameSprites;
	std::shared_ptr<AnimationClip>										   m_largeClip = nullptr;

#ifdef _DEBUG
	SpawnManager* m_spawnManager = nullptr;
#endif
	GameObject* m_eftObj;
};


