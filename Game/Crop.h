#pragma once

enum Crops {
	Eggplant = 0,
	Potato = 1,
	Pumpkin = 2,
	Nothing
};

enum Size {
	S = 0,
	M = 1,
	L = 2,
};

enum FarmRank
{
	Rank_A = 0,
	Rank_B = 1,
	Rank_C = 2,
};

class Crop : public MonoBehaviour
{
public:

	//void Awake()		  override;
	void Update(float dt) override;

	Size GetSize() { return m_size; }
	Crops	GetCropType() { return m_type; }

	void OnTriggerEnter(Collider* other) override;
	void OnTriggerExit(Collider* other) override;
	FarmRank GetFarmRank() { return m_rank; }

	void SetCropData(FarmRank rank, Crops type, std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> gameSprites, std::shared_ptr<AnimationClip> clip = nullptr, GameObject* msg);

protected:
	float m_growSpeed_M;
	float m_growSpeed_L;
	float m_elapsedTime = 0.0f;
	Size m_size = Size::S;
	Size m_maxSize;
	Crops	m_type;

	FarmRank m_rank;

	bool isSpawn = false;

	SpriteRenderer* m_SpriteRenderer;
	Animator* m_Animator;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_GameSprites;
	std::shared_ptr<AnimationClip>										   m_largeClip = nullptr;

	GameObject* m_steal_message;
};


