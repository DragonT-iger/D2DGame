#pragma once
class Baby : public MonoBehaviour
{
public:
	enum Thought
	{
		None,
		Pumpkin,
		Eggplant,
		Potato
	};

	void ChangeThink(Thought t);
	void OnInspectorGUI()             override;
private:
	void Awake() override;
	void Update(float deltaTime) override;


	//parent
	SpriteRenderer* m_parentSpriteRenderer;

	//babyThinkUI
	GameObject* m_babyThinkUI;
	SpriteRenderer* m_babySpriteRenderer;

	GameObject* m_ItemUI;
	SpriteRenderer* m_ItemUISpriteRenderer;
	
	
	Thought m_thoughtState = Thought::None;
};

