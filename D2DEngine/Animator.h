#pragma once
#include "MonoBehaviour.h"
#include "SpriteRenderer.h"


class Animator : public MonoBehaviour
{
public:
	Animator() = default;
	virtual ~Animator() = default;

	virtual void Awake() override { m_sRenderer = GetOwner()->GetComponent<SpriteRenderer>(); }

	// ��������Ʈ ������ ��Ʈ�� �ٲٴ°Ŷ�(���� �ٲ� ��)
	// �ִϸ��̼� ������ �ٲ��ִ°� �־����

private:
	SpriteRenderer* m_sRenderer = nullptr;
	//�ִϸ��̼� ���� �ӽ� �ʿ��ϰ�
};
