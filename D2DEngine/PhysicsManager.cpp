#include "pch.h"
#include "PhysicsManager.h"

void PhysicsManager::Step(float fixedDelta)
{
    Scene* scene = SceneManager::Instance().GetActiveScene();
    if (!scene) return;

    std::vector<Collider*> colliders;
    for (const auto& goPtr : scene->GetGameObjects())
    {
        GameObject* go = goPtr.get();
        if (!go->IsActive()) continue;

        Collider* col = go->GetComponent<Collider>();
        if (col) colliders.push_back(col);
    }

    const size_t n = colliders.size();
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = i + 1; j < n; ++j)
        {
            Collider* a = colliders[i];
            Collider* b = colliders[j];

            if (a->IsCollide(b))
            {
				a->OnTriggerEnter(b);
                b->OnTriggerEnter(a);
                // TODO : OnTriggerEnter / Stay / Exit ±¸Çö
            }
        }
    }
}
