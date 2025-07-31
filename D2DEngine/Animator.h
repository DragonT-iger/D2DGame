#pragma once
#include "MonoBehaviour.h"
#include "SpriteRenderer.h"
#include "AnimationClip.h"



class Animator : public MonoBehaviour
{
public:
	Animator() = default;
	virtual ~Animator() noexcept = default;

	virtual void Awake() override;

	virtual void Update(float deltaTime) override;

	void AddClip(const std::string& name, std::shared_ptr<AnimationClip> clip, bool loop = false);

	void ChangeState(const std::string& name);

	const std::string& GetCurState();

	void SetEntryState(const std::string& name);

	bool IsAnimeEnd() { return m_isEnd; }

	// ��������Ʈ ������ ��Ʈ�� �ٲٴ°Ŷ�(���� �ٲ� ��)
	// �ִϸ��̼� ������ �ٲ��ִ°� �־����
private:
	SpriteRenderer* m_sRenderer;
	std::unordered_map<std::string, std::shared_ptr<AnimationClip>> m_animations;
	std::unordered_map<std::string, bool>													m_loopmap;
	std::shared_ptr<AnimationClip>																	m_curClip;
	std::string																											m_curState;
	std::vector<FrameData>																			m_frameDatas;
	std::vector<FrameData>::iterator																m_curFrame;
	float 																										m_duration = 0.0f;

	bool																										m_curAnimeLoop;
	bool																														m_isEnd;
};
