#pragma once

class TutorialScene : public Scene
{
	void Awake() override;
	void Start() override;


	Camera* main_Cam = nullptr;

    GameObject* player = nullptr;
    Transform* player_T = nullptr;
    SpriteRenderer* player_S = nullptr;

    GameObject* m_background = nullptr;
    GameObject* m_outRangeUp = nullptr;
    GameObject* m_outRangeDown = nullptr;
    GameObject* m_outRangeRight = nullptr;
    GameObject* m_outRangeLeft = nullptr;
};

