#include "pch.h"
#include "TutorialHintTrigger.h"
#include "TutorialHint.h"

TutorialHintTrigger::TutorialHintTrigger(size_t hintIndex)
    : m_hintIndex(hintIndex)
{
}

void TutorialHintTrigger::Start()
{
    GameObject* hintObj = GameObject::Find("TutorialHint");
    if (hintObj)
        m_hint = hintObj->GetComponent<TutorialHint>();
}

void TutorialHintTrigger::OnTriggerEnter(Collider* other)
{
    if (!m_hint)
        return;

    if (other->GetOwner()->GetTag() == "Player")
        m_hint->ShowHint(m_hintIndex);
}
