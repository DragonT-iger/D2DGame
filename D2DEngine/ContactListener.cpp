#include "pch.h"
#include "ContactListener.h"


static std::pair<Collider*, Collider*> MakeSortedPair(Collider* a, Collider* b)
{
    return (a < b) ? std::pair<Collider*, Collider*>{ a,b } : std::pair<Collider*, Collider*>{ b,a };
}

void ContactListener::BeginContact(b2Contact* c)
{
    auto* a = reinterpret_cast<Collider*>(c->GetFixtureA()->GetUserData().pointer);
    auto* b = reinterpret_cast<Collider*>(c->GetFixtureB()->GetUserData().pointer);
    if (!a || !b) return;

    if (a->IsTrigger() || b->IsTrigger())
    {
        a->GetOwner()->BroadcastTriggerEnter(b);
        b->GetOwner()->BroadcastTriggerEnter(a);
        m_pairs.insert(MakeSortedPair(a, b));
    }
}

void ContactListener::EndContact(b2Contact* c)
{
    auto* a = reinterpret_cast<Collider*>(c->GetFixtureA()->GetUserData().pointer);
    auto* b = reinterpret_cast<Collider*>(c->GetFixtureB()->GetUserData().pointer);
    if (!a || !b) return;

    if (a->IsTrigger() || b->IsTrigger())
    {
        a->GetOwner()->BroadcastTriggerExit(b);
        b->GetOwner()->BroadcastTriggerExit(a);
        m_pendingErase.emplace_back(MakeSortedPair(a, b));
    }
}

void ContactListener::DispatchStayEvents()
{
    if (m_pairs.empty()) return;

    // 1) 스냅샷
    std::vector<Pair> snapshot;
    snapshot.reserve(m_pairs.size());
    snapshot.insert(snapshot.end(), m_pairs.begin(), m_pairs.end());

    // 2) 안전하게 순회 (컨테이너 변형 X)
    for (const auto& [a, b] : snapshot)
    {
        if (!a || !b) continue;
        a->GetOwner()->BroadcastTriggerStay(b);
        b->GetOwner()->BroadcastTriggerStay(a);
    }

    // 3) EndContact 에서 쌓아둔 항목 제거
    for (const auto& p : m_pendingErase)
        m_pairs.erase(p);
    m_pendingErase.clear();
}