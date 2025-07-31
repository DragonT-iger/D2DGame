#include "pch.h"
#include "GameObjectFindTest.h"

void GameObjectFindTest::Awake()
{
	player = GameObject::Find("Player");
}

void GameObjectFindTest::Start()
{
	player->GetComponent<Animator>()->SetActive(false);
}
