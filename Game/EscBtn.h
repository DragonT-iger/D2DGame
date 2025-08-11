#pragma once

class EscBtn : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

private:
	GameObject* m_EscBG;
	GameObject* m_TitleBtn;
	GameObject* m_SettingBtn;

	bool isActive = false;
};

