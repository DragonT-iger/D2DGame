#include "pch.h"
#include "Player.h"
#include "Baby.h"
#include "GameManager.h"
#include "Inventory.h"


float Baby::m_QExeCount = 0;

void Baby::Awake()
{

	m_parentSpriteRenderer = GetOwner()->GetComponent<SpriteRenderer>();

	m_babyThinkUI = Instantiate("BabyUI");
	auto tr = m_babyThinkUI->GetComponent<Transform>();
	tr->SetPosition({ 345.400f, 312.600f });

	tr->SetParent(GetOwner()->GetComponent<Transform>());
	m_babySpriteRenderer = m_babyThinkUI->AddComponent<SpriteRenderer>();

	m_babySpriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("BabyThink.png"));
	m_babySpriteRenderer->SetActive(false);

	m_ItemUI = Instantiate("ItemUI");

	m_ItemUISpriteRenderer = m_ItemUI->AddComponent<SpriteRenderer>();

	m_ItemUI->GetComponent<Transform>()->SetParent(GetOwner()->GetComponent<Transform>());

	m_player = GetComponent<Player>();

	m_inven_ptr = GameObject::Find("Inventory")->GetComponent<Inventory>();
}

void Baby::Update(float deltaTime)
{

	if (m_parentSpriteRenderer->IsFlip()) {
		m_babyThinkUI->GetComponent<Transform>()->SetPosition({ 345.400f, 312.600f });
		m_ItemUI->GetComponent<Transform>()->SetPosition({ 400.400f, 400.400f });
		m_babySpriteRenderer->SetFlip(false);
	}
	else {
		m_babyThinkUI->GetComponent<Transform>()->SetPosition({ -357.800f, 312.600f });
		m_ItemUI->GetComponent<Transform>()->SetPosition({ -400.400f, 400.400f });
		m_babySpriteRenderer->SetFlip(true);
	}

	QuestinProgress(deltaTime);
}


void Baby::ChangeThink(Thought t)
{
	if (t == Thought::None) {
		m_babySpriteRenderer->SetActive(false);
		m_ItemUISpriteRenderer->SetBitmap(nullptr);
		m_thoughtState = t;
		return;
	}
	if (t == Thought::Pumpkin) {
		m_ItemUISpriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("pumpkin_item.png"));
		m_ItemUISpriteRenderer->SetSize(250.f, 250.f);
	}
	else if (t == Thought::Eggplant) {
		m_ItemUISpriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("eggplant_item.png"));
		m_ItemUISpriteRenderer->SetSize(250.f, 250.f);
	}
	else if (t == Thought::Potato) {
		m_ItemUISpriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("potato_item.png"));
		m_ItemUISpriteRenderer->SetSize(250.f, 250.f);
	}

	m_babySpriteRenderer->SetActive(true);
	m_thoughtState = t;
}

void Baby::OnTriggerEnter(Collider* other)
{
	if (other->GetOwner()->GetTag() == "SubMissionArea")
	{
		int bob = GameManager::Instance().ReceiveScore(QuestDataCollector(m_inven_ptr->SubMissonItem()));
		m_player->FeedBaby(bob);

		if (m_QuestInProgress == true)
		{
			QuestExamine();
		}
	}
}

void Baby::OnTriggerExit(Collider* other)
{
	if (other->GetOwner()->GetTag() == "SubMissionArea")
	{
		if (0 <= m_QExeCount && m_QuestInProgress == false)
		{
			QuestSuggestions();
			m_QuestInProgress = true;
		}
	}
}

void Baby::OnInspectorGUI()
{
	static const char* kThoughtNames[] =
	{ "None", "Pumpkin", "Eggplant", "Potato" };

	int cur = static_cast<int>(m_thoughtState);
	if (ImGui::Combo("Thought", &cur,
		kThoughtNames, IM_ARRAYSIZE(kThoughtNames)))
	{
		ChangeThink(static_cast<Thought>(cur));
	}
}


void Baby::QuestSuggestions()
{
	int index = Random::Instance().Range(1, 4);
	ChangeThink(static_cast<Thought>(index));

	m_QuestInProgress = true;
}

void Baby::QuestinProgress(float deltaTime)
{
	if (m_QuestInProgress == true) // 퀘스트 진행중일 때만 카운트
	{
		m_QExeCount += deltaTime;
	}

	if (m_player->GetAction() == Action::Hit) //Hit failed
	{
		m_QExeCount -= 30;
		m_QuestInProgress = false;

		QuestFailed();
		return;
	}

	if (m_QExeTime < m_QExeCount) //time Out
	{
		m_QExeCount = 0;
		m_QuestInProgress = false;

		QuestFailed();
	}
}

void Baby::QuestSuccess()
{
	std::cout << "QuestSuccess" << std::endl;
	ChangeThink(Thought::None);

	temp_ep = 0;
	temp_pt = 0;
	temp_pk = 0;

	m_QExeCount -= 30;
}

void Baby::QuestFailed()
{
	std::cout << "QuestFailed" << std::endl;
	ChangeThink(Thought::None);
}

const std::vector<SlotData>& Baby::QuestDataCollector(const std::vector<SlotData>& data)
{
	for (auto& m : data)
	{
		switch (m.type)
		{
		case 0:
			temp_ep = m.count;
			std::cout << "temp_ep : " << temp_ep << std::endl;
			break;
		case 1:
			temp_pt = m.count;
			std::cout << "temp_pt : " << temp_pt << std::endl;
			break;
		case 2:
			temp_pk = m.count;
			std::cout << "temp_pk : " << temp_pk << std::endl;
			break;
		}
	}
	return data;
}

void Baby::QuestExamine()
{
	switch (m_thoughtState)
	{
	case Eggplant:
		if (0 < temp_ep) QuestSuccess(); return;
		break;
	case Potato:
		if (0 < temp_pt) QuestSuccess(); return;
		break;
	case Pumpkin:
		if (0 < temp_pk) QuestSuccess(); return;
		break;
	default: return;
	}
}


