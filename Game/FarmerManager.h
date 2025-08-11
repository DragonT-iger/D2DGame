#pragma once

class FarmerManager : public MonoBehaviour
{
public:
    void Awake() override;

private:
    std::vector<GameObject*> m_farmers;
    //FMOD::ChannelGroup* 
};