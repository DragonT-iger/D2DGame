#include "pch.h"
#include "Crop.h"
#include "InventorySlot.h"


void Slot::Start()
{
	m_image = GetComponent<Image>();
	m_image->SetActive(false);
}

void Slot::Update(float deltaTime)
{
	if (!m_data.isEmpty && m_data.count == 0)
		SetEmpty();

	SetText();
}

void Slot::RegisterText(Text* text)
{
	m_text = text;
	m_text->SetOrderLayer(3);
}

void Slot::AddItem(Crops type, Size count, Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite)
{
	if (m_data.isEmpty)
	{
		SetSprite(sprite);
		m_data.type = type;
		m_data.isEmpty = false;
	}
	if (m_data.type != type)//디버그용
	{
		std::cout << "현재 아이템 타입과 일치하지 않음" << std::endl;
		return;
	}
		
	if (count == S)
		m_data.count += 1;
	else
		m_data.count += static_cast<size_t>(count) * 3;
}

void Slot::ThrowItem()
{
	if(m_data.count > 0)
		m_data.count--;

	if (m_data.count == 0)
	{
		SetEmpty();
	}
}

SlotData Slot::ThrowAll()
{
	auto data = m_data;

	m_data.count = 0;
	SetEmpty();

	return data;
}

void Slot::SetSprite(Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite)
{
	auto slotSize = GetComponent<Transform>()->GetParent()->GetComponent<Image>()->GetSize();
	slotSize = { slotSize.width - 60, slotSize.height - 60 };
	m_image->SetActive(true);
	m_image->SetBitmap(sprite, slotSize);
}

void Slot::SetEmpty()
{
	m_image->SetActive(false);

	m_data.isEmpty = true;
	m_data.type = Nothing;
}

void Slot::SetText()
{
	std::wstring ws_Count = std::to_wstring(m_data.count);

	m_text->SetText(ws_Count, {20,20}, L"Maplestory");
	m_text->SetFontSize(15.0f);
}
