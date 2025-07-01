#pragma once
#include "Component.h"

class D2DRenderer : public MonoBehaviour {
public:
    virtual ~D2DRenderer() = default;
    virtual void Render() = 0;
    // 여기서 렌더링 구현
};
