#pragma once

class Player;

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

	void QuestSuggestions();
	void QuestinProgress(float deltaTime);

	int QuestSuccess();
	void QusetFalse();

	void SetExecutionTime(float time);

	void OnInspectorGUI()             override;
private:
	void Awake() override;
	void Update(float deltaTime) override;

	void OnTriggerExit(Collider* other) override;

	Player* m_player;
	//parent
	SpriteRenderer* m_parentSpriteRenderer;

	//babyThinkUI
	GameObject* m_babyThinkUI;
	SpriteRenderer* m_babySpriteRenderer;

	GameObject* m_ItemUI;
	SpriteRenderer* m_ItemUISpriteRenderer;
	
	Thought m_thoughtState = Thought::None;

	bool m_QuestInProgress = false;
	static float m_QExeCount;
	float m_QExeTime = 30;
};

