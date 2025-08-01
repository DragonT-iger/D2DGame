#pragma once
class StealMessage : public MonoBehaviour
{
	void Awake() override;
	void Start() override;
private:
	SpriteRenderer* sprite_stealmsg = nullptr;
		
};

