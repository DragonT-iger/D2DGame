#pragma once

class FarmerManager : public MonoBehaviour
{
public:
    virtual ~FarmerManager();
    void Awake() override;

    void PlayWarningSound();

    void WarningSoundStop();

private:
    std::vector<GameObject*> m_farmers;
    FMOD::ChannelGroup* m_farmerWarningGroup = nullptr;
};