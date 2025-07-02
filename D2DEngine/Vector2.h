#pragma once

/// 날짜 / 이름 / 수정내용
/// 2025-07-02 권용범 최초버전 작성

/// <summary>
/// Unity Like 벡터 클래스
/// </summary>
class Vector2
{
public:

	Vector2() : m_x(0.f), m_y(0.f) {}
	explicit Vector2(float x, float y) : m_x(x), m_y(y) {}

	// 연산자 오버로드

	Vector2 operator+(const Vector2& rhs); // R-value 지원
	Vector2 operator-(const Vector2& rhs);
	Vector2 operator*(float rhs);
	friend Vector2 operator*(float lhs, const Vector2& rhs); //  (float) * (Vector2) 일때 처리
	Vector2 operator/(float rhs); // 나누기는 순서 반대로 나누는건 굳이 지원 안해줌


	Vector2& operator+=(const Vector2& rhs);
	Vector2& operator*=(const Vector2& rhs);
	Vector2& operator/=(const Vector2& rhs);
	Vector2& operator-=(const Vector2& rhs); // float 더하기는 실수할까봐 그냥 지원 안해줌

	bool operator==(const Vector2& rhs) const;
	bool operator!=(const Vector2& rhs) const;


	Vector2& Scale(float scale);


	Vector2& Normalize();
	Vector2 Normalized() const; // 유니티는 n으로 시작하지만 일단 컨벤션을 위해 대문자로
	float Magnitude() const;
	float SqrMagnitude() const;

	static float Dot(const Vector2& lhs, const Vector2& rhs);
	static float Distance(const Vector2& a, const Vector2& b);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	//static Vector2 Reflect(const Vector2& inDirection, const Vector2& inNormal); // 필요할떄 구현


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
