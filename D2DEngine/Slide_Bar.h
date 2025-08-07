#pragma once

class Slide_Bar : public MonoBehaviour
{
public:
	Slide_Bar() = default;
	~Slide_Bar() = default;

	void Start() override;

	void UpdateWidthRatio(float v);
	void UpdateHeightRatio(float v);

	void RegisterButton(Button* handleButton);

	float GetValue() { return value; }

private:
	Image*						m_Image = nullptr;
	Button*					 m_button = nullptr;
	D2D1_SIZE_F			m_orignal = { 0,0 };
	float						value = 1.0f; //ÃÖ´ñ°ª 1.0
};
