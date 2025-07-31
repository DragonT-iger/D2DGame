#pragma once
class GameObjectFindTest : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;

private:

	GameObject* player;
};

