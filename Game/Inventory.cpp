#include "pch.h"
#include "Inventory.h"

void Inventory::Awake()
{
	m_SlotSprites.push_back(ResourceManager::Instance().LoadTexture("Icon_Frame.png"));
	m_SlotSprites.push_back(ResourceManager::Instance().LoadTexture("Icon_Frame_Selected.png"));

	auto slot1 = GameObject::Find("Slot1")->GetComponent<Slot>();
	auto slot2 = GameObject::Find("Slot2")->GetComponent<Slot>();
	auto slot3 = GameObject::Find("Slot3")->GetComponent<Slot>();

	m_slots.push_back(slot1);
	m_slots.push_back(slot2);
	m_slots.push_back(slot3);

	m_profile = GameObject::Find("playerProfile")->GetComponent<Image>();
	m_babyProfile = GameObject::Find("babyProfile")->GetComponent<Image>();
	m_hungry = GameObject::Find("hungryImg")->GetComponent<Image>();

	m_profiles.push_back(ResourceManager::Instance().LoadTexture("mom_profile1.png"));
	m_profiles.push_back(ResourceManager::Instance().LoadTexture("mom_profile2.png"));

	m_babyProfiles.push_back(ResourceManager::Instance().LoadTexture("baby_profile1.png"));
	m_babyProfiles.push_back(ResourceManager::Instance().LoadTexture("baby_profile2.png"));
	m_babyProfiles.push_back(ResourceManager::Instance().LoadTexture("baby_profile3.png"));

	m_hungrys.push_back(ResourceManager::Instance().LoadTexture("hungry1.png"));
	m_hungrys.push_back(ResourceManager::Instance().LoadTexture("hungry2.png"));
	m_hungrys.push_back(ResourceManager::Instance().LoadTexture("hungry3.png"));
}

void Inventory::Start()
{
	m_slots[Potato]->SetSprite(ResourceManager::Instance().LoadTexture("potato3_item_Whiteline.png"));
	m_slots[Eggplant]->SetSprite(ResourceManager::Instance().LoadTexture("eggplant3_item_Whiteline.png"));
	m_slots[Pumpkin]->SetSprite(ResourceManager::Instance().LoadTexture("pumpkin3_item_Whiteline.png"));

	m_curSlotNum = 0;
	m_curSlot = m_slots[m_curSlotNum];
	m_bgImage = m_curSlot->GetOwner()->GetComponent<Transform>()->GetParent()->GetOwner()->GetComponent<Image>();
	D2D1_SIZE_F size = m_bgImage->GetSize();
	m_bgImage->SetBitmap(m_SlotSprites[1], size);
}

void Inventory::SetMaxCount(std::array<size_t, 3> maxCounts)
{
	for (int i = 0; i < m_slots.size(); i++)
	{
		m_slots[i]->SetMaxCount(maxCounts[i]);
	}
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
	auto data = m_slots[type]->GetData();

	m_slots[type]->AddItem(type, size);
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

size_t Inventory::GetCropCount(Crops type)
{
	auto count = m_slots[type]->GetData().count;

	return count;
}

const SlotData& Inventory::GetCurSlotData()
{
	return m_curSlot->GetData();
}

Crops Inventory::ThrowItem()
{
	auto data = m_curSlot->GetData();

	if (data.isEmpty)
		return Crops::Nothing;

	m_curSlot->ThrowItem();

	return data.type;
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

void Inventory::UpdateBabyProfile(size_t index)
{
	if (index != m_babyIndex)
	{
		if (!m_babyProfile) {
			m_babyProfile->SetBitmap(m_babyProfiles[index], { 80, 80 });
			m_babyIndex = index;
		}
	}
}

void Inventory::UpdateProfile(size_t index)
{
	if (index != m_profileIndex)
	{
		if (!m_profile) {
			m_profile->SetBitmap(m_profiles[index], { 80, 80 });
			m_profileIndex = index;
		}
	}
}

void Inventory::UpdateHungryImg(size_t index)
{
	if (index != m_hungryIndex)
	{
		if (m_hungry) {
			m_hungry->SetBitmap(m_hungrys[index], { 65, 65 });
			m_hungryIndex = index;
		}
	}
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


