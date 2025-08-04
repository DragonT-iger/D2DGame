#include "pch.h"
#include "Crop.h"
#include "StealMessage.h"
#include "SpawnManager.h"


void SpawnManager::Awake()
{
	curScene = SceneManager::Instance().GetActiveScene();
	//���� ����
	farm_A = { -1070, 720, 1070, -720 };
	farm_B = { -2130, 1330, 2130, -1330};
	farm_C = { -3210, 2110, 3210, -2110 };
	Home = {-50, 50, 50, -50};
	
	farmArr.reserve(3);
	farmArr.push_back({ Rank_A, 20, 0.0f, 3.f, &m_farmAList });
	farmArr.push_back({ Rank_B, 15, 0.0f, 4.f, &m_farmBList });
	farmArr.push_back({ Rank_C, 10, 0.0f, 5.f, &m_farmCList });

	//����Ʈ �ʱ�ȭ
	m_farmAList.clear();
	m_farmBList.clear();
	m_farmCList.clear();
	m_farmAList.reserve(20);
	m_farmBList.reserve(15);
	m_farmCList.reserve(10);

	//���۹� ��������Ʈ ����
	m_effectSprite = ResourceManager::Instance().LoadAnimationClip("crop_sparkle.json", "sparkle");

	m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinS.png"));
	m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinM.png"));
	m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinL.png"));
	//m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinXL.png"));

	m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantS.png"));
	m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantM.png"));
	m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	//m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantXL.png"));
	
	m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoS.png"));
	m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoM.png"));
	m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoXL.png"));
	//m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoXL.png"));

	m_cropSprites.emplace(Pumpkin, &m_pumpkinSprite);
	m_cropSprites.emplace(Eggplant, &m_eggplantSprite);
	m_cropSprites.emplace(Potato, &m_potatoSprite);
}

void SpawnManager::Update(float deltaTime)
{
	for (auto& farm : farmArr)
	{
		if (farm.farmlist->size() <= farm.maxRate)
			farm.elapsedTime += deltaTime;

		if (farm.elapsedTime >= farm.spawnTime)
		{
			GameObject* obj = CreateNewCrop(farm.rank);
			farm.farmlist->push_back(obj);
			farm.elapsedTime = 0.f;
		}
	}
}

void SpawnManager::DestroyObject(GameObject* obj)
{
	auto rank = obj->GetComponent<Crop>()->GetFarmRank();

	switch (rank)
	{
	case Rank_A:
		for (auto it = m_farmAList.begin(); it != m_farmAList.end(); it++)
		{
			if (*it == obj)
			{
				m_farmAList.erase(it);
				break;
			}	
		}
		break;
	case Rank_B:
		for (auto it = m_farmBList.begin(); it != m_farmBList.end(); it++)
		{
			if (*it == obj)
			{
				m_farmBList.erase(it);
				break;
			}
		}
		break;
	case Rank_C:
		for (auto it = m_farmCList.begin(); it != m_farmCList.end(); it++)
		{
			if (*it == obj)
			{
				m_farmCList.erase(it);
				break;
			}
		}
		break;
	default:
		break;
	}
	curScene->Destroy(obj);
}

GameObject* SpawnManager::CreateNewCrop(FarmRank rank)
{
	Vector2 pos = { 0, 0 };

	GameObject* obj = Instantiate("crop");
	obj->SetTag("crop");

	auto sr = obj->AddComponent<SpriteRenderer>();
	auto box = obj->AddComponent<BoxCollider>();
	auto crop = obj->AddComponent<Crop>();

	GameObject* eftObj = Instantiate("effect");
	eftObj->SetActive(false);
	auto eft_sr = eftObj->AddComponent<SpriteRenderer>();
	auto eft_anim = eftObj->AddComponent<Animator>();
	eft_anim->AddClip("effect", m_effectSprite, true);
	
	eftObj->GetComponent<Transform>()->SetParent(obj->GetComponent<Transform>());
	eftObj->GetComponent<Transform>()->SetPosition({ 0.f, 0.f });

	Crops type = SetCropType(rank);

	SetCropData(crop, type, rank, eftObj);

	switch (rank)
	{
	case Rank_A:
		pos = CreateSpawnPoint(farm_A, Home, Rank_A);
		break;
	case Rank_B:
		pos = CreateSpawnPoint(farm_B, farm_A, Rank_B);
		break;
	case Rank_C:
		pos = CreateSpawnPoint(farm_C, farm_B, Rank_C);
		break;
	default:
		break;
	}

	obj->GetComponent<Transform>()->SetPosition(pos);
	obj->GetComponent<Transform>()->SetScale({0.5f, 0.5f});

	return obj;
}

bool SpawnManager::IsInnerRect(const RECT& rect, const int& x, const int& y)
{
	return (rect.left - 50 <= x && rect.right + 50 >= x) && (rect.top + 50 >= y && rect.bottom - 50 <= y);	// ��迡 �ڲ� �����ż� ���̸� �� ����ҵ�
}

bool SpawnManager::CheckRange(const Vector2& pos, FarmRank rank)
{
	switch (rank)
	{
	case Rank_A:
		for (const auto& obj : m_farmAList)
		{
			if (m_spawnRange >= Vector2::Distance(pos, obj->GetComponent<Transform>()->GetPosition()))
			{
				return true;
			}
		}
		return false;
		break;
	case Rank_B:
		for (const auto& obj : m_farmBList)
		{
			if (m_spawnRange >= Vector2::Distance(pos, obj->GetComponent<Transform>()->GetPosition()))
			{
				return true;
			}
		}
		return false;
		break;
	case Rank_C:
		for (const auto& obj : m_farmCList)
		{
			if (m_spawnRange >= Vector2::Distance(pos, obj->GetComponent<Transform>()->GetPosition()))
			{
				return true;
			}
		}
		return false;
		break;
	default:
		break;
	}
	return true;
}

Vector2 SpawnManager::CreateSpawnPoint(const RECT& outRect, const RECT& inRect, FarmRank rank)
{
	int x = 0;
	int y = 0;

	do {
		x = Random::Instance().Range(outRect.left, outRect.right);
		y = Random::Instance().Range(outRect.bottom, outRect.top);
	} while (IsInnerRect(inRect, x, y) || CheckRange({ static_cast<float>(x), static_cast<float>(y) }, rank));

	return { static_cast<float>(x),  static_cast<float>(y) };
}

Crops SpawnManager::SetCropType(FarmRank rank)
{
	int p = Random::Instance().Range(0, 9);

	switch (p)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		break;
	}

	Crops crop = static_cast<Crops>(p % 3);

	return  crop;
}

void SpawnManager::SetCropData(Crop* obj, Crops type, FarmRank rank, GameObject* eftObj)
{
	if (rank == Rank_C)
		obj->SetCropData(rank, type, *m_cropSprites.at(type), nullptr);
	else
		obj->SetCropData(rank, type, *m_cropSprites.at(type), eftObj);		//3�ܰ� �ִϸ��̼� ������ �߰�
}
