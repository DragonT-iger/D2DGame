// -------------------------------------------------------------
// Behaviour.h
// Adds simple on/off switch to a component (no lifecycle logic)
// -------------------------------------------------------------
#pragma once

#include "Component.h"

class Behaviour : public Component {
public:
    Behaviour() : m_enabled(true) {}
    virtual ~Behaviour() = default;

    void Enable() { m_enabled = true; }
    void Disable() { m_enabled = false; }
    void SetEnabled(bool state) { m_enabled = state; }
    bool IsEnabled() const { return m_enabled; }

private:
    bool m_enabled;
};
