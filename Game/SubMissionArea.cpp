#include "pch.h"
#include "Baby.h"
#include "SubMissionArea.h"

void SubMissionArea::Awake()
{
	m_boxCol = GetComponent<BoxCollider>();
	m_boxCol->SetSize(Vector2{ 521,4320 });
}