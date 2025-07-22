#pragma once
#include <unordered_set>

struct ColliderPairHash
{
    std::size_t operator()(const std::pair<Collider*, Collider*>& p) const noexcept
    {
        return std::hash<Collider*>()(p.first) ^ (std::hash<Collider*>()(p.second) << 1);
    }
};

class ContactListener final : public b2ContactListener
{
public:
    void BeginContact(b2Contact* c) override;
    void EndContact(b2Contact* c) override;
    void DispatchStayEvents();

private:
    using Pair = std::pair<Collider*, Collider*>;

    std::unordered_set<Pair, ColliderPairHash> m_pairs;
    std::vector<Pair>                          m_pendingErase;
};
