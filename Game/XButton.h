#pragma once

class XButton : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;

private:
	GameObject* OwnObject;
	Button*			  m_button;
};