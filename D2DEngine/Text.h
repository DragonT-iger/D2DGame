#pragma once

class Text : public MonoBehaviour
{
public:
	void Awake() override;
	void Start()	 override;
	void Update(float deltaTime) override;

private:
	std::wstring text;
	D2D1_RECT_F layoutRect;

}; 
