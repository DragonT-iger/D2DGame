#pragma once
class Tree : public MonoBehaviour
{

public:
	Tree(float x, float y , int tree) : m_x(x), m_y(y), m_tree(tree) {}

	void Awake() override;




private:
	float m_x = 0;
	float m_y = 0;
	int m_tree = -1;


	SpriteRenderer* m_spriteRenderer = nullptr;
	BoxCollider* m_boxCol = nullptr;
};

