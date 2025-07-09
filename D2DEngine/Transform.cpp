#include "pch.h"
#include "Transform.h"


void Transform::SetPivot(const Vector2& pivot)
{
	if(pivot.GetX() < 0.f || pivot.GetX() > 1.f || pivot.GetY() < 0.f || pivot.GetY() > 1.f){
		cwout << L"Pivot must be between 0 and 1." << std::endl;
		return;
	}
	m_pivot = pivot;
	m_dirty = true;
}

void Transform::SetParent(Transform* parent)
{
	assert(parent != this && "자기 자신을 부모로 설정할 수 없습니다.");

	if (m_parent != nullptr) {
		m_parent->DetachChildren();
	}
	
	m_parent = parent;
	parent->AddChild(this);

	SetDirty();
	//UpdateMatrices();

}

void Transform::DetachChildren()
{
	for (auto* c : m_children) {
		
	}
}

void Transform::AddChild(Transform* child)
{
}

void Transform::RemoveChild(Transform* child)
{
}

void Transform::Translate(const Vector2& delta)
{
}

void Transform::Translate(const float x, const float y)
{
}

void Transform::Rotate(float degree)
{
}

Vector2 Transform::GetForward() const
{
	return Vector2();
}

const Matrix3x2& Transform::GetLocalMatrix()
{
	// TODO: insert return statement here
}

const Matrix3x2& Transform::GetWorldMatrix()
{
	// TODO: insert return statement here
}

Matrix3x2 Transform::GetInverseWorldMatrix()
{
	return Matrix3x2();
}

Vector2 Transform::GetPivotPoint() const
{
	return Vector2();
}



void Transform::SetDirty()
{

	m_dirty = true;

	for (auto* child : m_children) {
		child->SetDirty();
	}
}

void Transform::UpdateMatrices()
{
}
