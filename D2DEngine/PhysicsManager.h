#pragma once

#include <box2d/box2d.h>

class PhysicsManager
{
public:
    static PhysicsManager& Instance()
    {
        static PhysicsManager Instance;
        return Instance;
    }

    void Initialize(const b2Vec2& gravity = { 0.0f, 9.8f }) { m_world = std::make_unique<b2World>(gravity); }
    void Step(float fixedDelta) { m_world->Step(fixedDelta, 8, 3); }
    b2World* Get() const { return m_world.get(); }

private:
    PhysicsManager() = default;
    std::unique_ptr<b2World> m_world;
};
