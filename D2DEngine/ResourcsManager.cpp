#include "pch.h"
#include "ResourcsManager.h"
#include "JsonParser.h"
#include "D2DRenderer.h"



void ResourceManager::AddTexture(D2DRenderer* renderer, std::wstring& key, const std::filesystem::path& filepath)
{

}

void ResourceManager::AddAnimationClip(D2DRenderer* renderer, std::wstring& key, const std::filesystem::path& filepath)
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
		clip.SetBitmap(sheet);
	}
}

Microsoft::WRL::ComPtr<ID2D1Bitmap1> ResourceManager::GetTexture(const std::wstring& key) const
{

}

std::shared_ptr<AnimationClip> ResourceManager::GetAnimationClip(const std::wstring& key) const
{
}
