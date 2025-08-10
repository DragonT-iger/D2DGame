#include "pch.h"
#include "GameObject.h"
#include "Animator.h"


void Animator::Awake()
{
	m_sRenderer = GetOwner()->GetComponent<SpriteRenderer>();
	if (m_sRenderer == nullptr) { assert(false && "애니메이터 사용시 스프라이트 렌더러 필요"); }
}

void Animator::Update(float deltaTime)
{
	if (m_isEnd || m_animations.empty())
		return;

	if (m_sRenderer->GetRenderInfo().m_bitmap == nullptr) return;



	if (m_curFrame->duration  <= m_duration )
	{
		++m_curFrame;
		if (m_curFrame == m_frameDatas.end() && m_curAnimeLoop)
		{
			m_curFrame = m_frameDatas.begin();
		}
		else if (m_curFrame == m_frameDatas.end() && !m_curAnimeLoop)
		{
			if(!m_isEnd) 
				m_isEnd = true;
			return;
		}
			
		m_sRenderer->SetSrcRect(m_curFrame->ToRectF());
		m_duration = 0.0f;
	}
	else {
		if (m_animationSpeed > 0.0f) {
			m_duration += deltaTime * m_animationSpeed;
		}

	}
		
}

void Animator::ChangeState(const std::string& name)
{
#ifdef _DEBUG
	if (m_animations.find(name) == m_animations.end())
	{
		throw std::runtime_error("Animator::ChangeState: Animation clip not found: " + name);
	}
#endif
	if (!m_sRenderer) m_sRenderer = GetOwner()->GetComponent<SpriteRenderer>();
	m_curClip = m_animations.at(name);
	m_curState = name;
	m_sRenderer->SetBitmap(m_curClip->GetBitmap());
	m_frameDatas = m_curClip->GetFrames();
	m_curFrame = m_frameDatas.begin();
	m_sRenderer->SetSrcRect(m_curFrame->ToRectF());
	m_curAnimeLoop = m_loopmap.at(name);
	m_isEnd = false;
}

const std::string& Animator::GetCurState()
{
	return m_curState;
}

void Animator::SetEntryState(const std::string& name)
{
	ChangeState(name);
}

void Animator::AddClip(const std::string& name, std::shared_ptr<AnimationClip> clip, bool isLoop)
{
	if (m_animations.empty())
	{
		m_animations.emplace(name, clip);
		m_loopmap.emplace(name, isLoop);
		SetEntryState(name);
	}
	else
	{
		m_animations.emplace(name, clip);
		m_loopmap.emplace(name, isLoop);
	}
}
