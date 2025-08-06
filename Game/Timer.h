#pragma once

class Timer : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;

	UINT GetCurTime() { return static_cast<UINT>(m_sceneTimer); }

private:
	float m_sceneTimer;
};