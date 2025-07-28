#include "pch.h"
#include "Image.h"

void Image::Start()
{
	m_pos = GetComponent<Transform>()->GetPosition();
}
