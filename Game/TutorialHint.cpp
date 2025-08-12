#include "pch.h"
#include "TutorialHint.h"

void TutorialHint::Awake()
{
    m_text = GetComponent<Text>();
    m_image = GetComponent<Image>();
}

void TutorialHint::SetHintTexts(const std::vector<std::wstring>& texts)
{
    m_texts = texts;
}

void TutorialHint::SetHintImages(const std::vector<std::string>& images, const Vector2& size)
{
    m_imageNames = images;
    m_imageSize = size;
}

void TutorialHint::ShowHint(size_t index)
{
    if (m_text && index < m_texts.size())
    {
        m_text->SetText(m_texts[index], { 500, 500 }, L"Maplestory", D2D1::ColorF::Black);
    }

    if (m_image && index < m_imageNames.size())
    {
        auto bitmap = ResourceManager::Instance().LoadTexture(m_imageNames[index]);
        m_image->SetBitmap(bitmap, { m_imageSize.x, m_imageSize.y });
    }
}