#pragma once

class FarmerManager : public MonoBehaviour
{
public:
    void Awake() override;

    void PlayWarningSound();
private:
    std::vector<GameObject*> m_farmers;
    FMOD::ChannelGroup* m_farmerWarningGroup = nullptr;
};