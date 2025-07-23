#include "pch.h"
#include "B2DebugDraw.h"

static D2D1::ColorF toD2(const b2Color& c) { return { c.r,c.g,c.b,0.8f }; }

void B2DebugDraw::DrawPolygon(const b2Vec2* v, int32 c, const b2Color& col)
{
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> b;
    m_dc->CreateSolidColorBrush(toD2(col), &b);

    for (int i = 0; i < c; ++i)
    {
        auto p1 = v[i], p2 = v[(i + 1) % c];
        m_dc->DrawLine({ p1.x * m_ppm,p1.y * m_ppm },
            { p2.x * m_ppm,p2.y * m_ppm }, b.Get());
    }
}

void B2DebugDraw::DrawCircle(const b2Vec2& cen, float r, const b2Color& col)
{
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> b;
    m_dc->CreateSolidColorBrush(toD2(col), &b);

    m_dc->DrawEllipse({ {cen.x * m_ppm,cen.y * m_ppm}, r * m_ppm, r * m_ppm }, b.Get());
}

void B2DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& col)
{
    Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> b;
    m_dc->CreateSolidColorBrush(toD2(col), &b);
    m_dc->DrawLine({ p1.x * m_ppm,p1.y * m_ppm }, { p2.x * m_ppm,p2.y * m_ppm }, b.Get());
}