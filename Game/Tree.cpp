#include "pch.h"
#include "Tree.h"
#include "YSort.h"
#include "GameManager.h"

void Tree::Awake()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	tr->SetPosition({ m_x, m_y });

	if (GameManager::Instance().GetGameState() != GameManager::GameState::Tutorial) {
		tr->Translate({ 0 , 200 });
	}

	tr->SetScale({ 0.5f, 0.5f });
	m_spriteRenderer = GetOwner()->AddComponent<SpriteRenderer>();

	YSort* ysort = GetOwner()->AddComponent<YSort>();
	ysort->SetOffset(100);
	m_boxCol = GetOwner()->AddComponent<BoxCollider>();



	GetOwner()->SetTag("OutRange");

	ComPtr<ID2D1Bitmap1> tree_sprite;

	if (m_tree == 0) {

		tree_sprite = ResourceManager::Instance().LoadTexture("tree_1.png");
	}
	else if (m_tree == 1) {

		tree_sprite = ResourceManager::Instance().LoadTexture("tree_2.png");
	}
	else if (m_tree == 2) {

		tree_sprite = ResourceManager::Instance().LoadTexture("tree_3.png");
	}
	else if (m_tree == 3) {

		tree_sprite = ResourceManager::Instance().LoadTexture("tree_4.png");
	}
	m_spriteRenderer->SetBitmap(tree_sprite);


	if (m_boxCol)
	{

		if (m_tree == 2 || m_tree == 3) {
		
			m_boxCol->SetSize(Vector2{ 100, 100 });
			m_boxCol->SetOffset({ 5.000f, -158.000f });
		}
		else {
			m_boxCol->SetSize(Vector2{ 100, 100 });
			m_boxCol->SetOffset({ 5.000f, -231.000f });
		}
	}
}
