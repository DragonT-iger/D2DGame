#include "pch.h"
#include "FarmerManager.h"
#include "Farmer.h"

void FarmerManager::Awake()
{
    std::vector<Vector2> positions = {
        {-1000.f,  1000.f},
        {    0.f,  1000.f},
        { 1000.f,  1000.f},
        {-1000.f,     0.f},
        {    0.f,     0.f},
        { 1000.f,     0.f},
        {-1000.f, -1000.f},
        {    0.f, -1000.f},
        { 1000.f, -1000.f}
    };

    m_farmers.reserve(positions.size());

    for (const auto& pos : positions)
    {
        GameObject* farmerObj = Instantiate("Farmer");
        farmerObj->AddComponent<Farmer>();
        farmerObj->GetComponent<Transform>()->SetPosition(pos);
        m_farmers.push_back(farmerObj);
    }
}