#pragma once

class CreditButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

private:
	Button* m_start;
	Button* m_setting;
	Button* m_quit;
	Button* m_button = nullptr;
	GameObject* m_credit = nullptr;
	GameObject* m_creditQuit = nullptr;
};

