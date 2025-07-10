#pragma once
#include "MonoBehaviour.h"
#include "SpriteRenderer.h"


class Animator : public MonoBehaviour
{
public:
	Animator() = default;
	virtual ~Animator() = default;

	virtual void Awake() override { m_sRenderer = GetOwner()->GetComponent<SpriteRenderer>(); }

	// 스프라이트 렌더러 비트맵 바꾸는거랑(상태 바뀔 때)
	// 애니메이션 프레임 바꿔주는거 있어야함

private:
	SpriteRenderer* m_sRenderer = nullptr;
	//애니메이션 상태 머신 필요하고
};
