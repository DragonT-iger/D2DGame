#include "pch.h"
#include "ResourcsManager.h"
#include "JsonParser.h"
#include "D2DRenderer.h"



void ResourceManager::AddTexture(D2DRenderer* renderer, std::string& key, const std::filesystem::path& filepath)
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

	renderer->CreateBitmapFromFile(filepath.wstring().c_str(), *sheet.GetAddressOf());

	if (!sheet)
	{
		std::cerr << "비트맵 생성 오류" << std::endl;
		return;
	}

	if (m_textures.find(key) == m_textures.end())
	{
		//이미 등록 된 키가 있으면, 리턴
		return;
	}
	m_textures.emplace(key, sheet);
}

void ResourceManager::AddAnimationClip(D2DRenderer* renderer, std::string& key, const std::filesystem::path& filepath)
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

	std::filesystem::path texturePath = filepath;
	texturePath.replace_extension(".png");

	renderer->CreateBitmapFromFile(texturePath.wstring().c_str(), *sheet.GetAddressOf());

	assert(sheet);

	m_textures.emplace(key, sheet);

	

	AnimationClips clips = JsonParser::Load(filepath);

	for(auto& clip : clips)
	{
		std::shared_ptr<AnimationClip> pclip = std::make_shared<AnimationClip>();
		*pclip = clip;
		pclip->SetBitmap(sheet);
		std::string newkey = key + "_" + clip.GetName();
		m_aniClips[newkey] = pclip;
	}
}

Microsoft::WRL::ComPtr<ID2D1Bitmap1> ResourceManager::GetTexture(const std::string& key) const
{
	if (m_textures.find(key) == m_textures.end())
	{
		std::cerr << "텍스처를 찾을 수 없습니다: " << key << std::endl;
		return nullptr;
	}
	return m_textures.find(key)->second;
}

std::shared_ptr<AnimationClip> ResourceManager::GetAnimationClip(const std::string& key) const
{
	auto it = m_aniClips.find(key);
	if(it == m_aniClips.end())
	{
		std::cerr << "애니메이션 클립을 찾을 수 없습니다: " << key << std::endl;
		return nullptr;
	}
	return it->second;
}
