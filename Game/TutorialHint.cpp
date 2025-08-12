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
    size_t finalIndex = m_texts.empty() ? 0 : m_texts.size() - 1;
    if (m_lastHintShown && index != finalIndex)
        return;

    if (m_text && index < m_texts.size())
    {
        m_text->SetText(m_texts[index], { 704.f, 404.f }, L"Maplestory", D2D1::ColorF::White);
    }

    if (m_image && index < m_imageNames.size())
    {
        auto bitmap = ResourceManager::Instance().LoadTexture(m_imageNames[index]);
        m_image->SetBitmap(bitmap, { m_imageSize.x, m_imageSize.y });


        if (index == finalIndex)
            m_lastHintShown = true;
    }
}