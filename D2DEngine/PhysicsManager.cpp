#include "pch.h"
#include "PhysicsManager.h"
#include "ContactListener.h"
#include "B2DebugDraw.h"

PhysicsManager& PhysicsManager::Instance() {
    static PhysicsManager Instance;
    return Instance;
}

void PhysicsManager::Initialize(const b2Vec2& gravity) {
	m_contactListener = std::make_unique<ContactListener>();
    m_world = std::make_unique<b2World>(gravity);
    m_world->SetContactListener(m_contactListener.get());

    m_debugDraw = std::make_unique<B2DebugDraw>(dc, ppm= 100.f);
    m_debugDraw->SetFlags(b2Draw::e_shapeBit);
}

void PhysicsManager::SetGravity(const b2Vec2& gravity) {
    m_world->SetGravity(gravity);
}

b2Vec2 PhysicsManager::GetGravity() const {
    return m_world->GetGravity();
}

void PhysicsManager::Step(float fixedDelta) {
    m_world->Step(fixedDelta, 8, 3);
	m_contactListener->DispatchStayEvents();
}

b2Body* PhysicsManager::CreateBody(const b2BodyDef& def)
{
    return m_world->CreateBody(&def);
}

b2World* PhysicsManager::Get() const {
    return m_world.get();
}

PhysicsManager::~PhysicsManager()
{
    if (m_world)
    {
        m_world->SetContactListener(nullptr);
    }

    m_world.reset();      

    m_contactListener.reset();
}



