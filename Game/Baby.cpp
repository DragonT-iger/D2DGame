#include "pch.h"
#include "Baby.h"

float Baby::deltaCount = 0;

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

	m_questTime = 10;
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

}

void Baby::ChangeThink(Thought t)
{
	if (t == Thought::None) {
		m_babySpriteRenderer->SetActive(false);
		m_ItemUISpriteRenderer->SetBitmap(nullptr);
		m_thoughtState = t;
		return;
	}
	else if (t == Thought::Pumpkin) {
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
	int index = Random::Instance().Range(1, 3);
	ChangeThink(static_cast<Thought>(index));
}

void Baby::QuestinProgress(float deltaTime)
{
	deltaCount += deltaTime;

	if (m_questTime < deltaCount)
	{
		
		deltaCount = 0;
	}
}

int Baby::QuestSuccess()
{
	return 0;
}

void Baby::QusetFalse()
{

}

void Baby::SetExecutionTime(float time)
{
	deltaCount = time;
}
