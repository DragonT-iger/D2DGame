#include "pch.h"
#include "SceneManager.h"

void SceneManager::RegisterScene(const std::wstring& name, std::unique_ptr<Scene> scene)
{
	auto result = m_scenes.emplace(name, std::move(scene));
	if (!result.second) {
		assert(false && "�̹� ��ϵ� �� �̸��Դϴ�.");
		return;
	}
}

void SceneManager::LoadScene(const std::wstring& name)
{
	Scene* prev = GetActiveScene(); // �� ó���� nullptr ��

	auto it = m_scenes.find(name);

	if(it == m_scenes.end()) {
		assert(false && "�������� �ʴ� �� �̸��Դϴ�.");
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
