#pragma once
//2025-07-10

///</summary>
// ResourceManager
///</summary>
// ����, �ؽ���, �ִϸ��̼� Ŭ�� ���� �� ���� ����
#include <unordered_map>
#include <filesystem>
#include "AnimationClip.h"



class D2DRenderer; //������ ���漱��, ��Ʈ�� ������ �ٸ� �� ����

class ResourceManager
{
	ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
public:
	~ResourceManager() = default;

	static ResourceManager& Instance()
	{
		static ResourceManager instance;
		return instance;
	}

	void AddTexture(D2DRenderer* renderer, std::string& key, const std::filesystem::path& filepath);
	void AddAnimationClip(D2DRenderer* renderer, std::string& key, const std::filesystem::path& filepath);

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetTexture(const std::string& key) const;
	std::shared_ptr<AnimationClip> GetAnimationClip(const std::string& key) const;

	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_textures;
	std::unordered_map<std::string, std::shared_ptr<AnimationClip>> m_aniClips;
	//std::unordered_map<std::wstring, ���� Ŭ����> m_sounds;	//���� ��
};
