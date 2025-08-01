#pragma once

struct ColliderInfo {
	Transform* m_transform;
	Collider* m_collider;
};

class Collider : public MonoBehaviour
{
public:
	virtual ~Collider() = default;

	void Awake() override { m_transform = GetComponent<Transform>(); }

	virtual bool IsCollide(const Collider* other) const = 0; // �̰ɷ� ������ LateUpdate���� �浹 ������ Ȯ���ϸ� ��

	Vector2	 GetOffset() const { return m_offset; }
	void	 SetOffset(const Vector2& newOffset) { m_offset = newOffset; }
	Vector2  GetCenter() const { return m_transform->GetWorldPosition() + m_offset * m_transform->GetScale(); }
	
	//����� ��
	virtual void DrawCollider() = 0;

	virtual ColliderInfo GetColliderInfo() = 0;

	virtual void OnInspectorGUI();

protected:
	Transform* m_transform = nullptr;
	Vector2    m_offset = { 0,0 };
	bool       m_isTrigger = true; // �⺻������ true�� �ֳ��ϸ� Rigidbody ������ ���� ��.. �׷�.. �ϴ��� Overlap
};

