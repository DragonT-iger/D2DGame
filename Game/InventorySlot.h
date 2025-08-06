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
	void Start() override;

	void Update(float deltaTime) override;

	SlotData GetData() { return m_data; }

	void AddItem(Crops type, Size count, Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite = nullptr);	//������ ó�� ���� �� ��������Ʈ ���ÿ�

	void ThrowItem();
	SlotData ThrowAll();
	
	void SetSprite(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite);

	void SetEmpty();

	void SetText();

private:
	SlotData m_data = { true, Nothing, 0 };

	Image* m_image;

	Text* m_text;
};
