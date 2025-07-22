#pragma once
#include "MonoBehaviour.h"
#include <box2d/box2d.h>

class Rigidbody2D : public MonoBehaviour {
public:
    enum class BodyType { Static, Dynamic, Kinematic };

    void Awake() override;
    void FixedUpdate(float fixedDelta) override;

    b2Body* GetBody() const { return m_body; }
    void   SetBodyType(BodyType type) { m_bodyType = type; }

private:
    BodyType m_bodyType = BodyType::Dynamic;
    b2Body* m_body = nullptr;
};
