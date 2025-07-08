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
