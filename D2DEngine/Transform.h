#pragma once
/// 날짜 / 이름 / 수정내용
/// 2025-07-08 최초버전 작성중

using Matrix3x2 = D2D1::Matrix3x2F;

/// <summary>
/// Transform 계층구조
/// </summary>
class Transform : public Component
{
public:
	

	Transform() = default; // 0 0 1 0 0 초기화

	// 로컬

	const Vector2& GetLocalPosition()		const { return m_localPosition; }
		  float	   GetLocalRotation()		const { return m_localRotation; }
	const Vector2& GetLocalScale()			const { return m_localScale; }
	const Vector2& GetPivot()				const { return m_pivot; }

	void SetLocalPosition(const Vector2& position) { m_localPosition = position; m_dirty = true; }
	void SetLocalRotation(float rotation)		   { m_localRotation = rotation; m_dirty = true; }
	void SetLocalScale(const Vector2& scale)	   { m_localScale = scale	   ; m_dirty = true; }
	void SetPivot(const Vector2& pivot);

	//계층구조 관련
	Transform* GetParent() const { return m_parent; }
	void SetParent(Transform* parent);
	void DetachChildren();

	void Translate(const Vector2& delta);
	void Translate(const float x, const float y);
	void Rotate(float degree);

	Vector2 GetForward() const;

	const Matrix3x2& GetLocalMatrix();
	const Matrix3x2& GetWorldMatrix();
	Matrix3x2 GetInverseWorldMatrix();

	Vector2 GetPivotPoint() const;


	~Transform() = default;

private:

	void AddChild(Transform* child);
	void RemoveChild(Transform* child);
	void SetDirty();
	void UpdateMatrices();

	bool m_dirty = false;

	Vector2 m_localPosition = { 0.f , 0.f };
	float m_localRotation = 0.f;
	Vector2 m_localScale = { 1.f, 1.f };

	Transform* m_parent = nullptr;
	std::vector<Transform*> m_children = {};

	Matrix3x2 m_matrixLocal = D2D1::Matrix3x2F::Identity();
	Matrix3x2 m_matrixWorld = D2D1::Matrix3x2F::Identity();

	Vector2 m_pivot = { 0.f, 0.f }; // 피봇은 -1 ~ 1 사이의 값 0이면 가운데
};

