#pragma once

/// ��¥ / �̸� / ��������
/// 2025-07-02 �ǿ�� ���ʹ��� �ۼ�

/// <summary>
/// Unity Like ���� Ŭ����
/// </summary>
class Vector2
{
public:

	Vector2() : m_x(0.f), m_y(0.f) {}
	explicit Vector2(float x, float y) : m_x(x), m_y(y) {}

	// ������ �����ε�

	Vector2 operator+(const Vector2& rhs); // R-value ����
	Vector2 operator-(const Vector2& rhs);
	Vector2 operator*(float rhs);
	friend Vector2 operator*(float lhs, const Vector2& rhs); //  (float) * (Vector2) �϶� ó��
	Vector2 operator/(float rhs); // ������� ���� �ݴ�� �����°� ���� ���� ������


	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator*=(const Vector2& rhs);
	Vector2& operator/=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs); // float ���ϱ�� �Ǽ��ұ�� �׳� ���� ������

	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;


	Vector2& Scale(float scale);


	Vector2& Normalize();
	Vector2 Normalized() const; // ����Ƽ�� n���� ���������� �ϴ� �������� ���� �빮�ڷ�
	float Magnitude() const;
	float SqrMagnitude() const;

	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static float Distance(const Vector2& a, const Vector2& b);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	//static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal); // �ʿ��ҋ� ����


	// SqrMagnitude 

	static const Vector2 zero;
	static const Vector2 one;
	static const Vector2 up;
	static const Vector2 down;
	static const Vector2 left;
	static const Vector2 right;
	
private:
	float m_x;
	float m_y;
};

Vector2 operator*(float lhs, Vector2 rhs);
