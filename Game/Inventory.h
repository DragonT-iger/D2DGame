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

private:
	std::unordered_map<Crops, Microsoft::WRL::ComPtr<ID2D1Bitmap1>>	m_itemSprite;
	std::vector<Slot*>	m_slots;

	Slot* m_curSlot;
	int m_curSlotNum;
	int maxSlotNum = 2;
};
