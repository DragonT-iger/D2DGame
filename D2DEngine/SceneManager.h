/// 날짜 / 이름 / 수정내용
/// 2025-07-13 권용범 최초버전 작성

#pragma once
#include "Scene.h"
class SceneManager {
public:
    static SceneManager& Instance() {
        static SceneManager instance;
        return instance;
    };

    // 씬 등록/활성화
    void    SetActiveScene(Scene* scene) { m_active = scene; }
    Scene*  GetActiveScene() const { return m_active; }
    void    LoadScene(std::unique_ptr<Scene> scene);
    void    ProcessSceneChange();
    void    UnInitialize();

    // player 관리






	// ---------- Debug -----------
    bool GetDebugMode() { return m_debugMode; }
	void SetDebugMode(bool active) { m_debugMode = active; }

private:
    SceneManager() = default;
    ~SceneManager() = default;
    
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(SceneManager&&) = delete;
	SceneManager& operator=(SceneManager&&) = delete;

    bool                                                                              m_debugMode = true;
    Scene*                                                                                m_active = nullptr;
  
    std::unique_ptr<Scene>       m_activeKeep;
    std::unique_ptr<Scene>       m_pendingScene;
};


//   일단 SceneManager에 정의 나중에 위치 수정
inline GameObject* Instantiate(const std::string& name = "GameObject")
{
    Scene* s = SceneManager::Instance().GetActiveScene();
    assert(s && "Instantiate: active scene is null!");
    return s->CreateGameObject(name);
}