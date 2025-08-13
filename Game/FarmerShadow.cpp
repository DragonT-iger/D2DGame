#include "pch.h"
#include "FarmerShadow.h"


void FarmerShadow::Awake()
{
	m_FarmerObj = GetComponent<Transform>()->GetParent()->GetOwner();
	m_spriteRenderer = GetComponent<SpriteRenderer>();
}

void FarmerShadow::Start()
{
	m_spriteRenderer->SetBitmap(ResourceManager::Instance().LoadTexture("Farmer_Shadow.png"));
}

void FarmerShadow::Update(float deltaTime)
{
	
	if (m_FarmerObj->GetComponent<SpriteRenderer>()->IsFlip())
	{
		std::cout << "farmer flip" << std::endl;
		m_spriteRenderer->SetFlip(true);
	}
	else
	{
		m_spriteRenderer->SetFlip(false);
	}
}
