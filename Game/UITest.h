#pragma once

class UITest : public MonoBehaviour
{
public:
	void Awake() override;

	void Start() override;

	void Update(float dt) override;

private:
	float				m_value;
	Slide_Bar* m_SlideBar;
};
