#pragma once
class UI_Score : public MonoBehaviour
{
public:
	void Awake() override;
	void Update(float deltaTime) override;
private:
	Text* m_Text = nullptr;
	//Image* m_Score_BG = nullptr;
};