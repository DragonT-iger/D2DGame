#pragma once

class CreditQuitButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start()	 override;

private:
	Button* m_start;
	Button* m_setting;
	Button* m_quit;
	Button* m_credit;
	Button* m_button = nullptr;
	GameObject* m_creditImg = nullptr;
};
