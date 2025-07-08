#pragma once
/// ��¥ / �̸� / ��������
/// 2025-07-08 ���ʹ��� �ۼ���

/// <summary>
/// Transform ��������
/// </summary>
class Transform : public Component
{
public:
	using Matrix3x2 = D2D1::Matrix3x2F;

	Transform() = default; // 0 0 1 0 0 �ʱ�ȭ

	// ����

	Vector2 GetLocalPosition()		const { return m_localPosition; } // �б� ���� �Լ� (const) ���ϰ� ���� -> �� �ֳĸ� Vector2���� �Լ��� ���밡���ؼ�
	float	GetLocalRotation()		const { return m_localRotation; }
	Vector2 GetLocalScale()			const { return m_localScale; }
	Vector2 GetPivot()				const { return m_pivot; }

	void SetLocalPosition(const Vector2& position) { m_localPosition = position; m_dirty = true; }
	void SetLocalRotation(float rotation)		   { m_localRotation = rotation; m_dirty = true; }
	void SetLocalScale(const Vector2& scale)	   { m_localScale = scale	   ; m_dirty = true; }
	void SetPivot(const Vector2& pivot);

	//�������� ����
	Transform* GetParent() const { return m_parent; }
	void SetParent(Transform* parent);
	void DetachChildren();
	void AddChild(Transform* child);
	void RemoveChild(Transform* child);

	void UpdateMatrices();

	~Transform() = default;

private:
	bool m_dirty;

	Vector2 m_localPosition = { 0.f , 0.f };
	float m_localRotation = 0.f;
	Vector2 m_localScale = { 1.f, 1.f };

	Transform* m_parent;
	std::vector<Transform*> m_children;

	Matrix3x2 m_matrixLocal = D2D1::Matrix3x2F::Identity();
	Matrix3x2 m_matrixWorld = D2D1::Matrix3x2F::Identity();

	Vector2 m_pivot = { 0.f, 0.f };
};

