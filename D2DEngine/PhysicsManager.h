#pragma once

class b2World;
class b2Vec2;
class ContactListener;
class b2BodyDef;
class b2Body;
class B2DebugDraw;

class PhysicsManager {
public:
    static      PhysicsManager& Instance();


    void        Initialize(const b2Vec2& gravity = b2Vec2{ 0.0f, -9.8f });

    void        SetGravity(const b2Vec2& gravity);
    b2Vec2      GetGravity() const;

    void        Step(float fixedDelta);

    b2Body*     CreateBody(const b2BodyDef& def);

    b2World*    Get() const;

private:
    PhysicsManager() = default;
    ~PhysicsManager();
    PhysicsManager(const PhysicsManager&) = delete;
    PhysicsManager& operator=(const PhysicsManager&) = delete;
    PhysicsManager(PhysicsManager&&) = delete;
    PhysicsManager& operator=(PhysicsManager&&) = delete;

    std::unique_ptr<ContactListener> m_contactListener;
    std::unique_ptr<b2World>         m_world;
	std::unique_ptr<B2DebugDraw>     m_debugDraw;
};
