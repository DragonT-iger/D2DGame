#include "pch.h"
#include "OpacityDown.h"

void OpacityDown::Awake()
{
	m_spriteRenderer = GetComponent<SpriteRenderer>();

	if (m_spriteRenderer == nullptr) {
		std::cout << "SpriteRenderer nullptr" << std::endl;
	}

}

void OpacityDown::Update(float deltaTime)
{
    m_spriteRenderer->SetOpacity(initialOpacity);

    static float fadeSpeed = 0.5f;
    initialOpacity -= fadeSpeed * deltaTime;

    if (initialOpacity < 0.0f)
        initialOpacity = 0.0f;
}