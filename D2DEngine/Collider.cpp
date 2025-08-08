#include "pch.h"
#include "Collider.h"



void Collider::OnInspectorGUI() {




	float offset[2] = { m_offset.x , m_offset.y };

	if (ImGui::DragFloat2("Offset", offset)) {
		SetOffset({ offset[0] , offset[1] });
	}
}


