#pragma once

class CreditButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

private:
	Button* m_button = nullptr;
	GameObject* m_credit = nullptr;
};

