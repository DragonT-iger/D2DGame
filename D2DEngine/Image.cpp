#include "pch.h"
#include "Image.h"

void Image::OnInspectorGUI()
{
    // 비트맵 핸들 표시
    ImGui::Text("Bitmap : %p", m_renderInfo.m_bitmap.Get());

    // SrcRect
    float src[4] = { m_renderInfo.m_srcRect.left,  m_renderInfo.m_srcRect.top,
                     m_renderInfo.m_srcRect.right, m_renderInfo.m_srcRect.bottom };
    if (ImGui::DragFloat4("SrcRect", src))
    {
        m_renderInfo.m_srcRect = { src[0], src[1], src[2], src[3] };
        SetSrcRect(m_renderInfo.m_srcRect);
    }

    // DestRect
    float dest[4] = { m_renderInfo.m_destRect.left,  m_renderInfo.m_destRect.top,
                      m_renderInfo.m_destRect.right, m_renderInfo.m_destRect.bottom };
    if (ImGui::DragFloat4("DestRect", dest))
    {
        m_renderInfo.m_destRect = { dest[0], dest[1], dest[2], dest[3] };
        SetDestRect(m_renderInfo.m_destRect);
    }

    // Size
    float size[2] = { m_size.width, m_size.height };
    if (ImGui::DragFloat2("Size", size))
    {
        m_size = { size[0], size[1] };
    }

    // Order in Layer
    int order = m_renderInfo.orderLayer;
    if (ImGui::DragInt("Order", &order))
    {
        SetOrderInLayer(order);
    }

    // 색상
    float color[4] = { m_renderInfo.m_color.r, m_renderInfo.m_color.g,
                       m_renderInfo.m_color.b, m_renderInfo.m_color.a };
    if (ImGui::ColorEdit4("Color", color))
    {
        m_renderInfo.m_color = D2D1::ColorF(color[0], color[1], color[2], color[3]);
    }

    // 텍스트 / 폰트 / 폰트 크기
    char textBuf[128] = {};
    std::string narrowText(m_renderInfo.m_text.begin(), m_renderInfo.m_text.end());
    strncpy_s(textBuf, narrowText.c_str(), _TRUNCATE);
    if (ImGui::InputText("Text", textBuf, sizeof(textBuf)))
    {
        // std::wstring 변환 필요
        static std::wstring wtext;
        wtext.assign(textBuf, textBuf + strlen(textBuf));
        m_renderInfo.m_text = wtext;
    }

    char fontBuf[128] = {};
    std::string narrowFont(m_renderInfo.m_font.begin(), m_renderInfo.m_font.end());
    strncpy_s(fontBuf, narrowFont.c_str(), _TRUNCATE);
    if (ImGui::InputText("Font", fontBuf, sizeof(fontBuf)))
    {
        static std::wstring wfont;
        wfont.assign(fontBuf, fontBuf + strlen(fontBuf));
        m_renderInfo.m_font = wfont;
    }

    int fontSize = m_renderInfo.fontSize;
    if (ImGui::DragInt("Font Size", &fontSize))
    {
        m_renderInfo.fontSize = fontSize;
    }
}
