#pragma once

class Text;
class Image;

class TutorialHint : public MonoBehaviour
{
public:
    void Awake() override;

    void ShowHint(size_t index);

    void SetHintTexts(const std::vector<std::wstring>& texts);
    void SetHintImages(const std::vector<std::string>& images, const Vector2& size = { 300.f, 100.f });

private:
    Text* m_text = nullptr;
    Image* m_image = nullptr;

    std::vector<std::wstring> m_texts;
    std::vector<std::string> m_imageNames;
    Vector2 m_imageSize{ 300.f, 100.f };
};
