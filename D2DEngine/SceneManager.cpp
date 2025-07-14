#include "pch.h"
#include "SceneManager.h"

void SceneManager::RegisterScene(const std::wstring& name, std::unique_ptr<Scene> scene)
{
	auto result = m_scenes.emplace(name, std::move(scene));
	if (!result.second) {
		assert(false && "이미 등록된 씬 이름입니다.");
		return;
	}
}

void SceneManager::LoadScene(const std::wstring& name)
{
	Scene* prev = GetActiveScene(); // 맨 처음은 nullptr 임

	auto it = m_scenes.find(name);

	if(it == m_scenes.end()) {
		assert(false && "존재하지 않는 씬 이름입니다.");
		return;
	}

	Scene* next = it->second.get();
	

	if (!m_active) {
		m_active->Awake();
		m_active->Start();
	}
	

#ifdef _DEBUG

	if(prev) cwout << "LoadScene: " << prev->GetName() << "->" << it->second.get()->GetName();
	else  cwout << "LoadScene: " << "Nothing" << "->" << it->second.get()->GetName();
	
#endif // !_DEBUG


	if(prev) prev->OnDisable();
	m_active = next;
	m_active->OnEnable();
}
