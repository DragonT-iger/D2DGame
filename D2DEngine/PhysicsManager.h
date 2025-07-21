#pragma once

class PhysicsManager
{
public:
    static PhysicsManager& Instance()
    {
        static PhysicsManager Instance;
        return Instance;
    }

    void Step(float fixedDelta);   // 충돌 검사

private:
    PhysicsManager() = default;
    ~PhysicsManager() = default;

    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;
    PhysicsManager(PhysicsManager&&) = delete;
    PhysicsManager& operator=(PhysicsManager&&) = delete;
};