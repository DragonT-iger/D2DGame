#pragma once

class B2DebugDraw : public b2Draw
{
public:
    explicit B2DebugDraw(ID2D1DeviceContext* dc, float ppm = 1.f)
        : m_dc(dc), m_ppm(ppm) {
    }

    // ��������: Solid �Լ��鿡�� �׳� Outline ������ �ѱ�ϴ�.
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
    ID2D1DeviceContext* m_dc;   // �ܺ� ���� Ÿ��
    float               m_ppm;  // Pixel-Per-Meter(1�̸� ��ȯ ����)
};