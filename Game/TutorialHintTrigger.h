#pragma once

class TutorialHint;
class Collider;

class TutorialHintTrigger : public MonoBehaviour
{
public:
    explicit TutorialHintTrigger(size_t hintIndex = 0);

    void Start() override;
    void OnTriggerEnter(Collider* other) override;

private:
    size_t m_hintIndex;
    TutorialHint* m_hint = nullptr;
};