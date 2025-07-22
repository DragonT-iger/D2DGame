#pragma once

class Transform;
class b2Fixture;

class Collider : public MonoBehaviour
{
public:
	virtual ~Collider() = default;

	void Awake() override { m_transform = GetComponent<Transform>(); CreateFixture(); }

	virtual bool IsCollide(const Collider* other) const = 0; // 이걸로 씬에서 LateUpdate에서 충돌 났는지 확인하면 됨

	virtual void CreateFixture() = 0;

	Vector2	 GetOffset() const { return m_offset; }
	void	 SetOffset(const Vector2& newOffset) { m_offset = newOffset; }
	Vector2  GetCenter() const { return m_transform->GetPosition() + m_offset; }

	bool     IsTrigger() const { return m_isTrigger; }

protected:
	b2Fixture* m_fixture = nullptr;
	Transform* m_transform = nullptr;
	Vector2    m_offset = { 0,0 };
	bool       m_isTrigger = true; // 기본적으로 true로 왜냐하면 Rigidbody 구현이 아직 좀.. 그럼.. 일단은 Overlap
};

