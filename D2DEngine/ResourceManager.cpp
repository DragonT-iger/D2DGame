#include "pch.h"
#include "ResourceManager.h"
#include "JsonParser.h"
#include "D2DRenderer.h"

namespace filesys = std::filesystem;


void ResourceManager::LoadPath()
{
	if (!filesys::exists(resourcePath) || !filesys::is_directory(resourcePath))
	{
		std::cerr << "��ȿ���� ���� ���丮 ����Դϴ�" << std::endl;
		return;
	}

	for (const auto& it : filesys::recursive_directory_iterator(resourcePath))
	{
		if(!it.is_regular_file()) continue;
		auto path = it.path();
		std::string key = path.filename().string();

		if (it.path().extension() == ".json")
		{
			std::cout << key << std::endl;

			m_JsonPaths.emplace(std::move(key), std::move(path));

			//cwout << "Json Path : " << path.wstring() << std::endl;
		}
		else if (it.path().extension() == ".png")
		{
			std::cout << key << std::endl;

			m_PngPaths.emplace(std::move(key), std::move(path));
		}
		else if (it.path().extension() == ".wav")
		{
			std::string parent = path.parent_path().string();

			if (parent.find("Sounds\\BGM") != std::string::npos)
			{
				std::cout << path << key << std::endl;
				m_BGMPaths.emplace(std::move(key), std::move(path));
			}
			else if (parent.find("Sounds\\SFX") != std::string::npos)
			{
				std::cout << key << std::endl;
				m_SFXPaths.emplace(std::move(key), std::move(path));
			}
			else if (parent.find("Sounds\\UI") != std::string::npos)
			{
				std::cout << key << std::endl;
				m_UIPaths.emplace(std::move(key), std::move(path));
			}
		}
		else if (it.path().extension() == ".mp3")
		{
			std::string parent = path.parent_path().string();

			if (parent.find("Sounds\\BGM") != std::string::npos)
			{
				std::cout << path << key << std::endl;
				m_BGMPaths.emplace(std::move(key), std::move(path));
			}
			else if (parent.find("Sounds\\SFX") != std::string::npos)
			{
				std::cout << key << std::endl;
				m_SFXPaths.emplace(std::move(key), std::move(path));
			}
			else if (parent.find("Sounds\\UI") != std::string::npos)
			{
				std::cout << key << std::endl;
				m_UIPaths.emplace(std::move(key), std::move(path));
			}
		}
	}
}

const ComPtr<ID2D1Bitmap1>& ResourceManager::LoadTexture(const std::string& key)
{
	if (m_PngPaths.find(key) == m_PngPaths.end())
	{
		std::cerr << "�߸��� ���� �̸� �Է� : " + key << std::endl;
		return nullptr;
	}

	auto path = m_PngPaths.at(key);

	if (m_textures.find(key) == m_textures.end()) //���� ����ϴ� �Ÿ� ��Ʈ�� ���
	{
		Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

		D2DRenderer::Instance().CreateBitmapFromFile(path.wstring().c_str(), *sheet.GetAddressOf());

		if (!sheet)
		{
			std::cerr << "��Ʈ�� ���� ����" << std::endl;
			return nullptr;
		}
		m_textures.emplace(key, sheet);
	}

	return m_textures.at(key);
}

std::shared_ptr<AnimationClip> ResourceManager::LoadAnimationClip(const std::string& key, const std::string& cliptag)
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sheet;

	if (m_JsonPaths.find(key) == m_JsonPaths.end())
	{
		std::cerr << "�߸��� ���� �̸� �Է� : " + key << std::endl;
		return nullptr;
	}

	auto path = m_JsonPaths.at(key);

	if (m_textures.find(key) == m_textures.end()) //������ ��Ʈ�� ���� ����ϰ� ������ �ִ°� ��������
	{
		filesys::path texturePath = path;
		texturePath.replace_extension(".png");

		D2DRenderer::Instance().CreateBitmapFromFile(texturePath.wstring().c_str(), *sheet.GetAddressOf());

		if (!sheet)
		{
			std::cerr << "��Ʈ�� ���� ����: " << texturePath.string() << std::endl;
			return nullptr;
		}
		m_textures.emplace(key, sheet);
	}
	else
	{
		sheet = m_textures[key];
	}

	if (m_aniClips.find(key + "_" + cliptag) == m_aniClips.end())	//Ŭ�� �±� json������ �´��� Ȯ�� ���� ��
	{
		AnimationClips clips = JsonParser::Load(path);

		for (auto& clip : clips)
		{
			std::shared_ptr<AnimationClip> pclip = std::make_shared<AnimationClip>(clip);
			pclip->SetBitmap(sheet);
			std::string newkey = key + "_" + clip.GetName(); //Ŭ�� �±� ���� �����ϰ� �ٲ� �� ������ ������
			std::cout << "new Key : " << newkey << std::endl;
			m_aniClips[newkey] = pclip;
		}
	}

	return m_aniClips.at(key + "_" + cliptag);
}
