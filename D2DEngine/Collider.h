#pragma once
class Collider : public Behaviour
{
public:
	virtual ~Collider() = default;

	Vector2 GetOffset() const { return offset; }
	void SetOffset(const Vector2& newOffset) { offset = newOffset; }


	virtual bool IsCollide(const Collider* other) const = 0; // 이걸로 씬에서 LateUpdate에서 충돌 났는지 확인하면 됨

protected:
	Vector2 offset = { 0 , 0 };
	bool isTrigger = true; // 기본적으로 true로 왜냐하면 Rigidbody 구현이 아직 좀.. 그럼.. 일단은 Overlap
};

