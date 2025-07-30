#pragma once
#include "Component.h"
/// ��¥ / �̸� / ��������
/// 2025-07-02 �ǿ�� ���ʹ��� �ۼ�

/// <summary>
/// ������Ʈ�� ���� �Ӽ� ����
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
