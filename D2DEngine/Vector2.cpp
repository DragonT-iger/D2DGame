#include "pch.h"
#include "Vector2.h"

Vector2 Vector2::operator+(Vector2 rhs)
{
	return Vector2(m_x + rhs.m_x, m_x + rhs.m_y);
}

Vector2 Vector2::operator-(Vector2 rhs)
{
	return Vector2();
}

Vector2 Vector2::operator*(float rhs)
{
	return Vector2();
}

Vector2 Vector2::operator/(float rhs)
{
	return Vector2();
}

Vector2 operator*(float lhs, Vector2 rhs)
{
	return Vector2();
}

Vector2& Vector2::operator+=(Vector2 rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;

	return *this;
}

Vector2& Vector2::operator*=(Vector2 rhs)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

Vector2& Vector2::operator/=(Vector2 rhs)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

Vector2& Vector2::operator-=(Vector2 rhs)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}

Vector2& Vector2::Scale(float scale)
{
	// TODO: ���⿡ return ���� �����մϴ�.
}
