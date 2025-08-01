#include "pch.h"
#include "Crop.h"
#include "InventorySlot.h"
#include "Inventory.h"

void Inventory::Awake()
{
	m_itemSprite.emplace(Eggplant, ResourceManager::Instance().LoadTexture("eggplant_item.png"));
	m_itemSprite.emplace(Potato, ResourceManager::Instance().LoadTexture("potato_item.png"));
	m_itemSprite.emplace(Pumpkin, ResourceManager::Instance().LoadTexture("pumpkin_item.png"));
}

void Inventory::Start()
{
	auto slot1 = GameObject::Find("Slot1")->GetComponent<Slot>();
	auto slot2 = GameObject::Find("Slot2")->GetComponent<Slot>();
	auto slot3 = GameObject::Find("Slot3")->GetComponent<Slot>();

	m_slots.push_back(slot1);
	m_slots.push_back(slot2);
	m_slots.push_back(slot3);

	m_curSlotNum = 0;
	m_curSlot = m_slots[m_curSlotNum];
}



void Inventory::AddCrop(Crops type, Size size)
{
	for (auto& slot : m_slots)
	{
		const auto& data = slot->GetData();
		if (data.isEmpty || data.type == type)
		{
			if (data.isEmpty)
				slot->AddItem(type, size, m_itemSprite[type]);
			else
				slot->AddItem(type, size);
		}
	}
}

void Inventory::ChangeSlot()
{
	m_curSlotNum++;
	if (m_curSlotNum > maxSlotNum)
		m_curSlotNum = 0;

	m_curSlot = m_slots[m_curSlotNum];
}

void Inventory::ThrowItem()
{
	m_curSlot->ThrowItem();
}

std::vector<SlotData> Inventory::SubMissonItem()
{
	std::vector<SlotData> datas;
	for (auto& slot : m_slots)
	{
		datas.push_back(slot->ThrowAll());
	}

	return datas;
}

int Inventory::GetWeight()
{
	int weight = 0;

	for (const auto& slot : m_slots)
	{
		const auto& data = slot->GetData();
		int w;

		switch (data.type)
		{
		case Eggplant:
			w = data.count * 25;
			break;
		case Potato:
			w = data.count * 10;
			break;
		case Pumpkin:
			w = data.count * 50;
			break;
		}

		weight += w;
	}

	return weight;
}



