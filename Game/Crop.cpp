#include "pch.h"
#include "Crop.h"
#ifdef  _DEBUG
#include "SpawnManager.h"
#endif //  



void Crop::Awake()
{
	m_size = Size::Born;
#ifdef _DEBUG
	m_spawnManager = GameObject::Find("SpawnManager")->GetComponent<SpawnManager>();
#endif
}

void Crop::Update(float deltaTime)
{
	if (!isSpawn || m_size == m_maxSize)
		return;

	switch (m_size)
	{
	case Born:
		if (m_elapsedTime >= m_growSpeed_S)
		{
			m_size = S;
			m_elapsedTime = 0.f;
			m_SpriteRenderer->SetBitmap(m_GameSprites[static_cast<size_t>(S)]);
			GetComponent<BoxCollider>()->SetActive(true);
		}
		else
			m_elapsedTime += deltaTime;
		break;
	case S:
		if (m_elapsedTime >= m_growSpeed_M)
		{
			m_size = M;
			m_elapsedTime = 0.f;
			m_SpriteRenderer->SetBitmap(m_GameSprites[static_cast<size_t>(M)]);
		}
		else
			m_elapsedTime += deltaTime;
		break;
	case M:
		if (m_elapsedTime >= m_growSpeed_L)
		{
			m_size = L;
			m_elapsedTime = 0.f;
			m_eftObj->SetActive(true);
			m_eftObj->GetComponent<SpriteRenderer>()->SetOrderInLayer(static_cast<int>(-GetComponent<Transform>()->GetPosition().y));
			m_SpriteRenderer->SetBitmap(m_GameSprites[static_cast<size_t>(L)]);
		}
		else
			m_elapsedTime += deltaTime;
		break;
	}
}

void Crop::OnTriggerEnter(Collider* other)
{
	
}

void Crop::OnTriggerExit(Collider* other)
{

}

void Crop::SetCropData(
											FarmRank rank,
											Crops type, 
											std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> gameSprites,
											GameObject* eftObj
											)
{
#ifdef _DEBUG
	if (!m_spawnManager)	 m_spawnManager = GameObject::Find("SpawnManager")->GetComponent<SpawnManager>();
#endif
	auto s = m_spawnManager->GetGrowSpeed(rank);
	m_growSpeed_S = s.growSpeedS;
	m_growSpeed_M = s.growSpeedM;
	m_growSpeed_L = s.growSpeedL;

	switch (rank)
	{
	case FarmRank::Rank_A:
	case FarmRank::Rank_B:
		m_maxSize = Size::L;
		break;
	case FarmRank::Rank_C:
		m_maxSize = Size::M;
		break;
	}

	m_rank = rank;
	m_type = type;
	m_GameSprites = gameSprites;

	m_SpriteRenderer = GetComponent<SpriteRenderer>();
	m_SpriteRenderer->SetBitmap(m_GameSprites[static_cast<size_t>(Born)]);

	if (eftObj)
	{
		m_eftObj = eftObj;
	}

	isSpawn = true;
}

void Crop::Destroy()
{
	SceneManager::Instance().GetActiveScene()->Destroy(m_eftObj);
}