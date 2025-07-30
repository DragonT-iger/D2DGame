#pragma once

class SpawnManager : public MonoBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;


private:
	float			m_spawnSpeed;

	RECT						   farm_A;
	RECT						   farm_B;
	RECT						   farm_C;
	RECT							 Home;

	int		m_maxRate_A;
	int		m_maxRate_B;
	int		m_maxRate_C;

	std::list<GameObject*> m_farmAList;
	std::list<GameObject*> m_farmBList;
	std::list<GameObject*> m_farmCList;
};
