#pragma once
#include "SceneManager.h"

class ClientSceneManager {
public:
    static ClientSceneManager& Instance() {
        static ClientSceneManager inst;
        return inst;
    }

    void LoadScene(std::unique_ptr<Scene> scene);
    void ProcessSceneChange();

private:
    ClientSceneManager() = default;
    ~ClientSceneManager() = default;

    ClientSceneManager(const ClientSceneManager&) = delete;
    ClientSceneManager& operator=(const ClientSceneManager&) = delete;
    ClientSceneManager(ClientSceneManager&&) = delete;
    ClientSceneManager& operator=(ClientSceneManager&&) = delete;

    bool m_pendingChange = false;
};