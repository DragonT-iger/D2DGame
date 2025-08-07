#include "pch.h"
#include "Baby.h"
#include "SubMissionArea.h"

void SubMissionArea::Awake()
{
	m_boxCol = AddComponent<BoxCollider>();
	m_boxCol->SetSize(Vector2{ 521,4320 });
}

void SubMissionArea::Start()
{
	m_baby = SceneManager::Instance().GetActiveScene()->GetPlayer()->GetComponent<Baby>();
}

void SubMissionArea::OnTriggerExit(Collider* other)
{

}
