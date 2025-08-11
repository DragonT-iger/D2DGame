#pragma once
#include "InventorySlot.h"
class Player;
class Inventory;
class SlotData;

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

	void QuestSuccess();
	void QuestFailed();

	void QuestExamine();

	void FeedMore(int bob);

	const std::vector<SlotData>& QuestDataCollector(const std::vector<SlotData>& data);

	void OnInspectorGUI()             override;
private:
	void Awake() override;
	void Update(float deltaTime) override;

	void OnTriggerEnter(Collider* other) override;
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


	//QuestSystem
	Inventory* m_inven_ptr = nullptr;

	static float m_QExeCount;

	bool m_QuestInProgress = false;

	bool m_QuestisTimeOut = false;
	float m_QExeTime = 8;

	int temp_ep = 0;
	int temp_pt = 0;
	int temp_pk = 0;
};

