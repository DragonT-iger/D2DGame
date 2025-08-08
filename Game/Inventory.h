#pragma once
#include "InventorySlot.h"

class Inventory : public MonoBehaviour
{
public:
	Inventory() = default;
	~Inventory() noexcept override = default;

	void Awake() override;
	void Start() override;

	void Update(float deltaTime) override;

	void AddCrop(Crops type, Size size);

	void ChangeSlot();

	void ThrowItem();

	std::vector<SlotData> SubMissonItem();

	float GetWeight();

	float GetSpeedMultiplier() const;

	void OnInspectorGUI() override;
	
private:
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>>		m_SlotSprites;
	std::vector<Slot*>	m_slots;
	Image*				m_bgImage;

	Slot* m_curSlot;
	int m_curSlotNum;
	int maxSlotNum = 2;

	double m_potatoBonus = 0.005;  
	double m_eggplantBonus = 0.01; 
	double m_pumpkinBonus = 0.015;  
};
