#include "pch.h"
#include "Transform.h"

Transform::Transform()
{
	m_position = { 0.f, 0.f };
	m_rotation = 0.f;
	m_scale = { 1.f, 1.f };
	m_parent = nullptr;
	m_dirty = false;
	m_matrixLocal = D2D1::Matrix3x2F::Identity();
	m_matrixWorld = D2D1::Matrix3x2F::Identity();
}

Transform::Transform(Vector2 position, float rotation, Vector2 scale, Transform* parent)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	m_parent = parent;
	m_dirty = true;
}
