#include "pch.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "GameObject.h"

void PhysicsManager::Step(float fixedDelta)
{
    Scene* scene = SceneManager::Instance().GetActiveScene();
    if (!scene) return;

    // 1) 이번 프레임 충돌 결과를 담을 컨테이너
    std::unordered_set<CollisionPair, CollisionPairHash> currCollisions;

    // 2) 활성 Collider 수집
    std::vector<Collider*> colliders;
    colliders.reserve(scene->GetGameObjects().size());
    for (const auto& goPtr : scene->GetGameObjects())
    {
        GameObject* go = goPtr.get();
        if (!go->IsActive()) continue;

        if (auto* col = go->GetComponent<Collider>())
            colliders.push_back(col);
    }

	// 3) 모든 페어 검사 (O(n^2)) 개선 가능하긴함 대충 ~1000개정도 콜라이더까진 괜찮은걸로 알고있음 근데 obb로 계산할꺼라 더 연산 부하 심함
    const size_t n = colliders.size();
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            Collider* a = colliders[i];
            Collider* b = colliders[j];

            if (!a->IsCollide(b)) continue;

            // 충돌한 페어는 정렬한 뒤 currCollisions 에 저장
            CollisionPair pair{ a, b };
            if (reinterpret_cast<uintptr_t>(a) > reinterpret_cast<uintptr_t>(b))
                std::swap(pair.a, pair.b);

            currCollisions.insert(pair);

            // ───── OnTriggerEnter or OnTriggerStay 판정 ─────
            if (m_prevCollisions.find(pair) == m_prevCollisions.end())
            {
                // 새롭게 부딪힘 → Enter
                a->GetOwner()->BroadcastTriggerEnter(b);
                b->GetOwner()->BroadcastTriggerEnter(a);
            }
            else
            {
                // 이전에도 있었음 → Stay
                a->GetOwner()->BroadcastTriggerStay(b);
                b->GetOwner()->BroadcastTriggerStay(a);
            }
        }
    }

    // 4) 이전에는 있었지만 이번에 없는 페어 = Exit
    for (const auto& pair : m_prevCollisions)
    {
        if (currCollisions.find(pair) != currCollisions.end())
            continue; // 여전히 충돌 중

        // 충돌 종료
        pair.a->GetOwner()->BroadcastTriggerExit(pair.b);
        pair.b->GetOwner()->BroadcastTriggerExit(pair.a);
    }

    // 5) 다음 프레임을 위해 prev ← curr
    m_prevCollisions.swap(currCollisions);
}
