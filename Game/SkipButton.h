#pragma once

class SkipButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start()	 override;

private:
	Button* m_button;
};

