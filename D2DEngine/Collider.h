#pragma once
class Collider : public Behaviour
{
public:
	virtual ~Collider() = default;

	Vector2 GetOffset() const { return offset; }
	void SetOffset(const Vector2& newOffset) { offset = newOffset; }


	virtual bool IsCollide(const Collider* other) const = 0; // �̰ɷ� ������ LateUpdate���� �浹 ������ Ȯ���ϸ� ��

protected:
	Vector2 offset = { 0 , 0 };
	bool isTrigger = true; // �⺻������ true�� �ֳ��ϸ� Rigidbody ������ ���� ��.. �׷�.. �ϴ��� Overlap
};

