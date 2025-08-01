#include "pch.h"
#include "StealMessage.h"

void StealMessage::Awake()
{
	sprite_stealmsg = GetComponent<SpriteRenderer>();
}

void StealMessage::Start()
{
	sprite_stealmsg->SetBitmap(ResourceManager::Instance().LoadTexture("steal_message.png"));
}
