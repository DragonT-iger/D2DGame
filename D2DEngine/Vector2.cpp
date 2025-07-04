#include "pch.h"
#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(m_x + rhs.m_x, m_y + rhs.m_y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(m_x - rhs.m_x, m_y - rhs.m_y);
}

Vector2 Vector2::operator*(float rhs) const
{
	return Vector2(m_x * rhs, m_y * rhs);	
}

Vector2 Vector2::operator/(float rhs) const
{
	return Vector2(m_x / rhs, m_y / rhs);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& rhs)
{
	m_x *= rhs.m_x;
	m_y *= rhs.m_y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& rhs)
{
	m_x /= rhs.m_x;
	m_y /= rhs.m_y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	return *this;
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return m_x == rhs.m_x && m_y == rhs.m_y;
}

bool Vector2::operator!=(const Vector2& rhs) const
{

	return m_x != rhs.m_x || m_y != rhs.m_y;
}

Vector2& Vector2::Scale(float scale)
{
	this->m_x * scale;
	this->m_y * scale;
	return *this;
}

Vector2& Vector2::Normalize()
{
	float length = std::sqrt(m_x * m_x + m_y * m_y);
	if (length != 0.0f)
	{
		m_x /= length;
		m_y /= length;
	}
	return *this;
}

Vector2 Vector2::Normalized() const
{
	float length = sqrt(m_x * m_x + m_y * m_y);
	if (length != 0.0f)
	{
		return Vector2(m_x / length, m_y / length);
	}
	return Vector2(0.0f, 0.0f);
}

float Vector2::Magnitude() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

float Vector2::SqrMagnitude() const
{
	return m_x * m_x + m_y * m_y;
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.m_x * rhs.m_x + lhs.m_y * rhs.m_y;
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
	return (a - b).Magnitude();
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	return Vector2(a.m_x + (b.m_x - a.m_x) * t, a.m_y + (b.m_y - a.m_y) * t);
}

Vector2 operator*(float lhs, const Vector2& rhs)
{
	return Vector2(rhs.m_x * lhs, rhs.m_y * lhs);
}

const Vector2 Vector2::zero(0.f, 0.f);
const Vector2 Vector2::one(1.f, 1.f);
const Vector2 Vector2::up(0.f, 1.f);
const Vector2 Vector2::down(0.f, -1.f);
const Vector2 Vector2::left(-1.f, 0.f);
const Vector2 Vector2::right(1.f, 0.f);