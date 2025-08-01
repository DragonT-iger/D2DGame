#pragma once
class BoxCollider : public Collider
{
public:
	void Awake() override;
	Vector2 GetSize() const { return size; }
	void SetSize(const Vector2& newSize) { size = newSize; }

	bool IsCollide(const Collider* other) const override;


	//디버그용
	void DrawCollider() override;

	ColliderInfo GetColliderInfo() override { 
		/*if (!m_transform)
			m_transform = GetComponent<Transform>();*/
		return { m_transform, this };
	} 

	void OnInspectorGUI() override;

private:
	Vector2 size = { 1, 1 }; // 상대적 크기 아님
};

