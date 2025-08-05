#pragma once


class Text : public MonoBehaviour
{
public:
	Text() = default;
	virtual ~Text() = default;

	void Awake() override;
	void Start()	 override;
	void Update(float deltaTime) override;

	void SetText(const std::wstring& newtext, const D2D1_SIZE_F& size, const WCHAR* font, const D2D1::ColorF& color = D2D1::ColorF::White) { 
		text = newtext; m_size = size; 
		m_renderInfo.m_font = font; 
		m_renderInfo.m_color = color;
	}
	void SetText(const std::wstring& newtext, const UINT& width, const UINT& height, const WCHAR* font, const D2D1::ColorF& color = D2D1::ColorF::White) {
		text = newtext; m_size.width = width; m_size.height = height; 
		m_renderInfo.m_font = font;
		m_renderInfo.m_color = color;
	}

	void SetFontSize(size_t size) { fontSize = size; }

	const UIRenderInfo& GetRenderInfo() {
		m_renderInfo.fontSize = fontSize;
		m_renderInfo.m_text = text.c_str();
		return m_renderInfo; 
	}

private:
	size_t											fontSize;
	D2D1_SIZE_F							m_size = { 0,0 };
	std::wstring								text;
	UIRenderInfo				m_renderInfo;
	Transform*				m_transform = nullptr;
}; 
