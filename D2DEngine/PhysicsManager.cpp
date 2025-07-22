#include "pch.h"
#include "PhysicsManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "GameObject.h"

void PhysicsManager::Step(float fixedDelta)
{
    Scene* scene = SceneManager::Instance().GetActiveScene();
    if (!scene) return;

    // 1) �̹� ������ �浹 ����� ���� �����̳�
    std::unordered_set<CollisionPair, CollisionPairHash> currCollisions;

    // 2) Ȱ�� Collider ����
    std::vector<Collider*> colliders;
    colliders.reserve(scene->GetGameObjects().size());
    for (const auto& goPtr : scene->GetGameObjects())
    {
        GameObject* go = goPtr.get();
        if (!go->IsActive()) continue;

        if (auto* col = go->GetComponent<Collider>())
            colliders.push_back(col);
    }

	// 3) ��� ��� �˻� (O(n^2)) ���� �����ϱ��� ���� ~1000������ �ݶ��̴����� �������ɷ� �˰����� �ٵ� obb�� ����Ҳ��� �� ���� ���� ����
    const size_t n = colliders.size();
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            Collider* a = colliders[i];
            Collider* b = colliders[j];

            if (!a->IsCollide(b)) continue;

            // �浹�� ���� ������ �� currCollisions �� ����
            CollisionPair pair{ a, b };
            if (reinterpret_cast<uintptr_t>(a) > reinterpret_cast<uintptr_t>(b))
                std::swap(pair.a, pair.b);

            currCollisions.insert(pair);

            // ���������� OnTriggerEnter or OnTriggerStay ���� ����������
            if (m_prevCollisions.find(pair) == m_prevCollisions.end())
            {
                // ���Ӱ� �ε��� �� Enter
                a->GetOwner()->BroadcastTriggerEnter(b);
                b->GetOwner()->BroadcastTriggerEnter(a);
            }
            else
            {
                // �������� �־��� �� Stay
                a->GetOwner()->BroadcastTriggerStay(b);
                b->GetOwner()->BroadcastTriggerStay(a);
            }
        }
    }

    // 4) �������� �־����� �̹��� ���� ��� = Exit
    for (const auto& pair : m_prevCollisions)
    {
        if (currCollisions.find(pair) != currCollisions.end())
            continue; // ������ �浹 ��

        // �浹 ����
        pair.a->GetOwner()->BroadcastTriggerExit(pair.b);
        pair.b->GetOwner()->BroadcastTriggerExit(pair.a);
    }

    // 5) ���� �������� ���� prev �� curr
    m_prevCollisions.swap(currCollisions);
}
