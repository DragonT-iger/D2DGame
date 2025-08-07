#pragma once
class SubMissionArea : public MonoBehaviour
{
public:
	void Awake()                         override;
	void Start()						 override;
	void OnTriggerExit(Collider* other)  override;

private:
	Baby* m_baby = nullptr;
	BoxCollider* m_boxCol = nullptr;
}

