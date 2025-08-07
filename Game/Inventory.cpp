#include "pch.h"
#include "Inventory.h"

void Inventory::Awake()
{
	m_itemSprite.emplace(Eggplant, ResourceManager::Instance().LoadTexture("eggplant_item.png"));
	m_itemSprite.emplace(Potato, ResourceManager::Instance().LoadTexture("potato_item.png"));
	m_itemSprite.emplace(Pumpkin, ResourceManager::Instance().LoadTexture("pumpkin_item.png"));
	m_SlotSprites.push_back(ResourceManager::Instance().LoadTexture("Icon_Frame.png"));
	m_SlotSprites.push_back(ResourceManager::Instance().LoadTexture("Icon_Frame_Selected.png"));
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
	m_bgImage = m_curSlot->GetOwner()->GetComponent<Transform>()->GetParent()->GetOwner()->GetComponent<Image>();
	D2D1_SIZE_F size = m_bgImage->GetSize();
	m_bgImage->SetBitmap(m_SlotSprites[1], size);
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

	if (Input.GetKeyPressed(Keycode::A))
	{
		int w = GetWeight();
		auto datas = SubMissonItem();

		//std::cout << "현재 무게 : " << w << std::endl;

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

			slot->SetText();
			break;
		}
	}
}

void Inventory::ChangeSlot()
{
	m_curSlotNum++;
	if (m_curSlotNum > maxSlotNum)
		m_curSlotNum = 0;

	D2D1_SIZE_F size = m_bgImage->GetSize();
	m_bgImage->SetBitmap(m_SlotSprites[0], size);

	m_curSlot = m_slots[m_curSlotNum];
	m_bgImage = m_curSlot->GetOwner()->GetComponent<Transform>()->GetParent()->GetOwner()->GetComponent<Image>();
	m_bgImage->SetBitmap(m_SlotSprites[1], size);
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

float Inventory::GetWeight()
{
	float weight = 0;

	for (const auto& slot : m_slots)
	{
		const auto& data = slot->GetData();
		
		if (data.isEmpty)
			continue;

		float w = 0;
		float decrease = 1;

		switch ((data.count)/3)
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
		default:
			decrease = 0.7f;
			break;
		}

		for (int i = 0; i < data.count; i++)
		{
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
	}
	//std::cout << weight << std::endl;
	return weight;
}

float Inventory::GetSpeedMultiplier() const
{
    std::size_t potato   = 0;
    std::size_t eggplant = 0;
    std::size_t pumpkin  = 0;

    for (const auto& slot : m_slots)
    {
        const auto& data = slot->GetData();
        if (data.isEmpty) continue;

        switch (data.type)
        {
        case Potato:   potato   += data.count; break;
        case Eggplant: eggplant += data.count; break;
        case Pumpkin:  pumpkin  += data.count; break;
        default: break;
        }
    }

    double mult = 1.0;
	mult *= std::pow(1.0 + m_potatoBonus, static_cast<double>(potato));
	mult *= std::pow(1.0 + m_eggplantBonus, static_cast<double>(eggplant));
	mult *= std::pow(1.0 + m_pumpkinBonus, static_cast<double>(pumpkin));
	return static_cast<float>(mult);
}

void Inventory::OnInspectorGUI()
{
	ImGui::Separator();
	ImGui::Text("Speed Bonus per Item");

	float potatoPerc = static_cast<float>(m_potatoBonus * 100.0);
	float eggplantPerc = static_cast<float>(m_eggplantBonus * 100.0);
	float pumpkinPerc = static_cast<float>(m_pumpkinBonus * 100.0);

	if (ImGui::DragFloat("Potato  (%)", &potatoPerc, 0.001f, 0.0f, 100.0f)) m_potatoBonus = potatoPerc / 100.0;
	if (ImGui::DragFloat("Eggplant(%)", &eggplantPerc, 0.001f, 0.0f, 100.0f)) m_eggplantBonus = eggplantPerc / 100.0;
	if (ImGui::DragFloat("Pumpkin (%)", &pumpkinPerc, 0.001f, 0.0f, 100.0f)) m_pumpkinBonus = pumpkinPerc / 100.0;
}


