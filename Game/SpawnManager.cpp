#include "pch.h"
#include "Crop.h"
#include "SpawnManager.h"


void SpawnManager::Awake()
{
	//구역 설정
	farm_A = { -1120, 771, 1120, -771 };
	farm_B = { -2182, 1387, 2182, -1387};
	farm_C = { -3264, 2160, 3264, -2160 };
	Home = {-50, 50, 50, -50};
	
	//스폰 시간 설정
	m_spawnTimeA = 3.f;
	m_spawnTimeB = 4.f;
	m_spawnTimeC = 5.f;

	m_elapsedTimeA = 0.f;
	m_elapsedTimeB = 0.f;
	m_elapsedTimeC = 0.f;

	//구역 별 최대 스폰 개수 설정
	m_maxRate_A = 20;
	m_maxRate_B = 15;
	m_maxRate_C = 10;

	//리스트 초기화
	m_farmAList.clear();
	m_farmBList.clear();
	m_farmCList.clear();

	//농작물 스프라이트 설정
	m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinS.png"));
	m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinM.png"));
	m_pumpkinSprite.push_back(ResourceManager::Instance().LoadTexture("pumpkinL.png"));

	m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantS.png"));
	m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantM.png"));
	m_eggplantSprite.push_back(ResourceManager::Instance().LoadTexture("eggplantL.png"));
	
	m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoS.png"));
	m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoM.png"));
	m_potatoSprite.push_back(ResourceManager::Instance().LoadTexture("potatoL.png"));
}

void SpawnManager::Start()
{
	std::random_device rd;
	gen.seed(rd());
}

void SpawnManager::Update(float deltaTime)
{
	m_elapsedTimeA += deltaTime;
	m_elapsedTimeB += deltaTime;
	m_elapsedTimeC += deltaTime;

	if (m_elapsedTimeA >= m_spawnTimeA && m_farmAList.size() <= m_maxRate_A)
	{
		GameObject* obj = CreateNewCrop(Rank_A);
		m_farmAList.push_back(obj);
		m_elapsedTimeA = 0.f;
		std::cout << "farm A spawn" << std::endl;
	}

	if (m_elapsedTimeB >= m_spawnTimeB && m_farmBList.size() <= m_maxRate_B)
	{
		GameObject* obj = CreateNewCrop(Rank_B);
		m_farmBList.push_back(obj);
		m_elapsedTimeB = 0.f;
		std::cout << "farm B spawn" << std::endl;
	}

	if (m_elapsedTimeC >= m_spawnTimeC && m_farmCList.size() <= m_maxRate_C)
	{
		GameObject* obj = CreateNewCrop(Rank_C);
		m_farmCList.push_back(obj);
		m_elapsedTimeC = 0.f;
		std::cout << "farm C spawn" << std::endl;
	}
}

GameObject* SpawnManager::CreateNewCrop(FarmRank rank)
{
	Vector2 pos = { 0, 0 };

	GameObject* obj = Instantiate("crop");
	
	auto sr = obj->AddComponent<SpriteRenderer>();
	auto box = obj->AddComponent<BoxCollider>();
	auto crop = obj->AddComponent<Crop>();
	Crops type = SetCropType();

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

	SetCropData(crop, type, rank);
	obj->GetComponent<Transform>()->SetPosition(pos);
	obj->GetComponent<Transform>()->SetScale({0.5f, 0.5f});
	//box->SetSize({ sr->GetSize().width, sr->GetSize().height });

	return obj;
}

bool SpawnManager::IsInnerRect(const RECT& rect, const int& x, const int& y)
{
	return (rect.left <= x && rect.right >= x) && (rect.top >= y && rect.bottom <= y);
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
	Random posX(outRect.left, outRect.right);
	Random posY(outRect.bottom, outRect.top);

	int x = 0;
	int y = 0;

	do {
		x = posX(gen);
		y = posY(gen);
	} while (IsInnerRect(inRect, x, y) && CheckRange({ static_cast<float>(x), static_cast<float>(y) }, rank));

	return { static_cast<float>(x),  static_cast<float>(y) };
}

Crops SpawnManager::SetCropType()
{
	Random type(0, 2);

	Crops crop = static_cast<Crops>(type(gen));

	return  crop;
}

void SpawnManager::SetCropData(Crop* obj, Crops type, FarmRank rank)
{
	switch (type)
	{
	case Pumpkin:
		obj->SetCropData(rank, type, m_pumpkinSprite);
		break;
	case Eggplant:
		obj->SetCropData(rank, type, m_eggplantSprite);
		break;
	case Potato:
		obj->SetCropData(rank, type, m_potatoSprite);
		break;
	default:
		break;
	}
}
