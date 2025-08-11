#pragma once
class OpacityDown : public MonoBehaviour
{
	
public:
	void Awake() override;
	void Update(float deltaTime) override;





private:
	float initialOpacity = 0.8f;




	SpriteRenderer* m_spriteRenderer = nullptr;
};

