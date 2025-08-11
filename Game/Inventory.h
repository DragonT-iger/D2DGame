#pragma once
#include "InventorySlot.h"

class Inventory : public MonoBehaviour
{
public:
	Inventory() = default;
	~Inventory() noexcept override = default;

	void Awake() override;
	void Start() override;

	void SetMaxCount(std::array<size_t, 3> maxCounts);

	void Update(float deltaTime) override;

	void AddCrop(Crops type, Size size);

	void ChangeSlot();

	size_t GetCropCount(Crops type);

	Crops ThrowItem();
	const SlotData& GetCurSlotData();

	std::vector<SlotData> SubMissonItem();

	void UpdateBabyProfile(size_t index);
	void UpdateProfile(size_t index);
	void UpdateHungryImg(size_t index);

	float GetWeight();

	float GetSpeedMultiplier() const;

	void OnInspectorGUI() override;
	
private:
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>		m_SlotSprites;
	std::vector<Slot*>	m_slots;
	Image*						m_bgImage;
	Image*						m_profile;
	Image*						m_babyProfile;
	Image*						m_hungry;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_profiles;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_babyProfiles;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_hungrys;

	Slot* m_curSlot;
	int m_curSlotNum;
	int maxSlotNum = 2;

	int m_profileIndex = 0;
	int m_babyIndex = 0;
	int m_hungryIndex = 0;

	double m_potatoBonus = 0.004;  
	double m_eggplantBonus = 0.01; 
	double m_pumpkinBonus = 0.024;  
};
