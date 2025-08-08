#pragma once
#include "Crop.h"

struct SlotData {
	bool isEmpty;
	Crops type;
	size_t count;
};

class Slot : public MonoBehaviour
{
public:
	void Awake() override;

	void Update(float deltaTime) override;

	void RegisterText(Text* text);

	SlotData GetData() { return m_data; }

	void AddItem(Crops type, Size count);	

	void ThrowItem();
	SlotData ThrowAll();

	void SetMaxCount(size_t maxCount) { m_maxCount = maxCount; }
	
	void SetSprite(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite);

	void SetEmpty();

	void SetText();

private:
	SlotData m_data = { true, Nothing, 0 };

	Image* m_image;

	Text* m_text;

	size_t m_maxCount = 0;
};
