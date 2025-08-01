#include "pch.h"
#include "Crop.h"

void Crop::Update(float deltaTime)
{
	if (!isSpawn || m_size == m_maxSize)
		return;

	switch (m_size)
	{
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
			if(m_largeClip)
				m_Animator->ChangeState("large");
			else
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
											std::shared_ptr<AnimationClip> clip,
											GameObject* msg
											)
{
	switch (rank)
	{
	case FarmRank::Rank_A:
	{
		m_growSpeed_M = 7.f; //sec
		m_growSpeed_L = 7.f; //sec
		m_maxSize = Size::L;
		break;
	}
	case FarmRank::Rank_B:
	{
		m_growSpeed_M = 7.f; //sec
		m_growSpeed_L = 12.f; //sec
		m_maxSize = Size::L;
		break;
	}
	case FarmRank::Rank_C:
	{
		m_growSpeed_M = 12.f; //sec
		m_growSpeed_L = 0.f; //sec //C등급은 최대 M까지
		m_maxSize = Size::M;
		break;
	}
	}

	m_rank = rank;
	m_type = type;
	m_GameSprites = gameSprites;
	m_steal_message = msg;

	m_SpriteRenderer = GetComponent<SpriteRenderer>();
	m_SpriteRenderer->SetBitmap(m_GameSprites[static_cast<size_t>(S)]);

	if (clip)
	{
		m_Animator = GetComponent<Animator>();
		m_largeClip = clip;
		m_Animator->AddClip("large", m_largeClip, true);
	}

	isSpawn = true;
}
