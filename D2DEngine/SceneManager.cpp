#include "pch.h"
#include "SceneManager.h"


void SceneManager::LoadScene(std::unique_ptr<Scene> scene)
{
	m_pendingScene = std::move(scene);
}

void SceneManager::ProcessSceneChange()
{
    if (!m_pendingScene)
        return;

    Scene* prev = m_active;

    if (prev) {
        prev->OnDisable();
        prev->UnInitialize();
    }

    m_activeKeep = std::move(m_pendingScene);
    m_active = m_activeKeep.get();

#ifdef _DEBUG
    //std::cout << L"[SceneManager] Load "
    //    << (prev ? prev->GetName() : "None")
    //    << "  " << m_active->GetName() << std::endl;
    //    << "  " << m_active->GetName() << std::endl;
#endif

    m_active->Awake();
    m_active->Start();
}

void SceneManager::UnInitialize()
{
	if (m_active)
		m_active->UnInitialize();
}
