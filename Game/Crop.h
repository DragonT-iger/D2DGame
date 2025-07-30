#pragma once

enum Crops {
	Eggplant = 0,
	Potato = 1,
	Pumpkin = 2,
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

	void Update(float dt) override;

	Size GetSize() { return m_size; }
	Crops	GetCropType() { return m_type; }

	void SetCropData(FarmRank rank, Crops type, std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> gameSprites);

protected:
	float m_growSpeed_M;
	float m_growSpeed_L;
	float m_elapsedTime = 0.0f;
	Size m_size = Size::S;
	Size m_maxSize;
	Crops	m_type;

	bool isSpawn = false;

	SpriteRenderer* m_SpriteRenderer;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_GameSprites;
};


