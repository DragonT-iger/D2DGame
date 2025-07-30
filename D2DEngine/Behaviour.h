#pragma once
#include "Component.h"
/// 날짜 / 이름 / 수정내용
/// 2025-07-02 권용범 최초버전 작성

/// <summary>
/// 컴포넌트를 껐다 켤수 있음
/// </summary>
class Behaviour : public Component {
public:
    Behaviour() : m_active(true) {}
    virtual ~Behaviour() = default;

    void Enable() { m_active = true; }
    void Disable() { m_active = false; }
    void SetActive(bool state) { m_active = state; }
    bool IsActive() const { return m_active; }

private:
    bool m_active;
};
