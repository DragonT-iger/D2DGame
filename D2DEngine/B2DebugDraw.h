#pragma once

class B2DebugDraw : public b2Draw
{
public:
    explicit B2DebugDraw(ID2D1DeviceContext* dc, float ppm = 1.f)
        : m_dc(dc), m_ppm(ppm) {
    }

    // 윤곽선만: Solid 함수들에서 그냥 Outline 쪽으로 넘깁니다.
    void DrawPolygon(const b2Vec2* v, int32 c, const b2Color& col) override;
    void DrawSolidPolygon(const b2Vec2* v, int32 c, const b2Color& col) override
    {
        DrawPolygon(v, c, col);
    }

    void DrawCircle(const b2Vec2& cen, float r, const b2Color& col) override;
    void DrawSolidCircle(const b2Vec2& cen, float r, const b2Vec2&, const b2Color& col) override
    {
        DrawCircle(cen, r, col);
    }

    void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& col) override;

private:
    ID2D1DeviceContext* m_dc;   // 외부 렌더 타겟
    float               m_ppm;  // Pixel-Per-Meter(1이면 변환 없음)
};