#include "pch.h"
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

void Inventory::Update(float deltaTime)
{
	if (Input.GetKeyPressed(Keycode::Q))
	{
		AddCrop(Eggplant, S);
	}
	if (Input.GetKeyPressed(Keycode::W))
	{
		AddCrop(Potato, S);
	}
	if (Input.GetKeyPressed(Keycode::E))
	{
		AddCrop(Pumpkin, S);
	}
	if (Input.GetKeyPressed(Keycode::X))
	{
		ChangeSlot();
		std::cout << m_curSlotNum << std::endl;
		std::cout << m_curSlot->GetData().count << std::endl;
	}
	if (Input.GetKeyPressed(Keycode::C))
	{
		ThrowItem();
	}
	if (Input.GetKeyPressed(Keycode::A))
	{
		int w = GetWeight();
		auto datas = SubMissonItem();

		std::cout << "현재 무게 : " << w << std::endl;

		for (const auto& data : datas)
		{
			switch (data.type)
			{
			case Eggplant:
				std::cout << "가지 : " << data.count << std::endl;
				break;
			case Potato:
				std::cout << "감자 : " << data.count << std::endl;
				break;
			case Pumpkin:
				std::cout << "호박 : " << data.count << std::endl;
				break;
			default:
				break;
			}
		}
	}
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

			break;
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
	if (!m_invenDirty) return -1;

	int weight = 0;

	for (const auto& slot : m_slots)
	{
		const auto& data = slot->GetData();
		
		if (data.isEmpty)
			continue;
		int w = 0;
		int decrease = 0;

		switch ((data.count + 1)/3)
		{
		case 0:
			decrease = 1;
			break;
		case 1:
			decrease = 0.9f;
			break;
		case 2:
			decrease = 0.8f;
			break;
		case 3:
			decrease = 0.7f;
			break;
		}

		switch (data.type)
		{
		case Eggplant:
			
			w = decrease * 25;
			break;
		case Potato:
			w = decrease * 10;
			break;
		case Pumpkin:
			w = decrease * 50;
			break;
		}

		weight += w;
	}

	Inventory::SetInvenDirty();

	return weight;
}



