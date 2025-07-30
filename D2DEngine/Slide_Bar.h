#pragma once

class Slide_Bar : public MonoBehaviour
{
public:
	Slide_Bar() = default;
	~Slide_Bar() = default;

	void Start() override;

	void UpdateWidthRatio(float v);
	void UpdateHeightRatio(float v);

private:
	Image*					 m_Image;
	D2D1_SIZE_F			m_orignal;
	float						value = 1.0f; //ÃÖ´ñ°ª 1.0
};
