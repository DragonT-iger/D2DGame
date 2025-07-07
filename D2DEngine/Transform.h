#pragma once
/// 날짜 / 이름 / 수정내용
/// 2025-07-07 최초버전 작성중

/// <summary>
/// Transform 계층구조
/// </summary>
class Transform : public Component
{
public:
	using Matrix3x2 = D2D1::Matrix3x2F;

	Transform(); // 0 0  1 0 0 초기화
	Transform(Vector2 position, float rotation, Vector2 scale, Transform* parent);
	Transform* GetParent() const { return m_parent; }

	~Transform() = default;

private:
	bool m_dirty;

	Vector2 m_position = { 0.f , 0.f };
	float m_rotation = 0.f;
	Vector2 m_scale = { 1.f, 1.f };

	Transform* m_parent;
	std::vector<Transform*> m_children;

	Matrix3x2 m_matrixLocal = D2D1::Matrix3x2F::Identity();
	Matrix3x2 m_matrixWorld = D2D1::Matrix3x2F::Identity();

	Vector2 m_pivot = { 0.f, 0.f };
};

