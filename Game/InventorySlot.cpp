#include "pch.h"
#include "Crop.h"
#include "InventorySlot.h"


void Slot::Awake()
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

void Slot::AddItem(Crops type, Size count)
{
	if (m_data.isEmpty)
	{
		m_data.isEmpty = false;
		m_data.type = type;
	}
		
	if (count == S)
		m_data.count += 1;
	else
		m_data.count += static_cast<size_t>(count) * 3;

	if (m_data.count >= m_maxCount)
	{
		m_data.count = m_maxCount;

		m_fullImage->SetActive(true);
		//떨구는 사운드 여기서 재생할듯
	}
}

void Slot::ThrowItem()
{
	if (m_fullImage->IsActive())
		m_fullImage->SetActive(false);

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

void Slot::RegisterFullImage(Image* fullImage)
{
	m_fullImage = fullImage;

	m_fullImage->SetBitmap(ResourceManager::Instance().LoadTexture("Icon_Full_Text.png"), { 117, 117 });
	m_fullImage->SetActive(false);

	m_fullImage->GetOwner()->GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
}

void Slot::SetEmpty()
{
	m_data.isEmpty = true;
	m_data.type = Nothing;
}

void Slot::SetText()
{
	std::wstring ws_Count = std::to_wstring(m_data.count);

	m_text->SetText(ws_Count, {30,30}, L"Maplestory");
	m_text->SetFontSize(15.0f);
}
