#include "pch.h"
#include "PlayerController_Sample.h"


void PlayerController_Sample::Awake()
{
    m_transform = GetComponent<Transform>();
    m_spriteRenderer = GetComponent<SpriteRenderer>();
    m_animator = GetComponent<Animator>();

    WRL::ComPtr<ID2D1Bitmap1> bitmap;
    //D2DRenderer::Instance().CreateBitmapFromFile(L"Assets/Player.png", *bitmap.GetAddressOf());

    //m_spriteRenderer->SetBitmap(bitmap);
    //m_spriteRenderer->SetSize(64.f, 64.f);
}

void  PlayerController_Sample::Start()
{
	auto molewalk = ResourceManager::Instance().LoadAnimationClip("sample_mole_1.json", "Walk");

	m_animator->AddClip("Walk", molewalk);
    m_animator->SetEntryState("Walk");
	curAnim = "Walk";

	auto collider = GetComponent<BoxCollider>();

	if (collider) {
		collider->SetSize({ m_spriteRenderer->GetSize().width, m_spriteRenderer->GetSize().height });
	}
	else {
		GetComponent<CircleCollider>()->SetRadius({ m_spriteRenderer->GetSize().width / 2 });
	}

	//m_spriteRenderer->SetOpacity(0.5f);
}


void PlayerController_Sample::Update(float deltatime)
{
	/*m_transform->Translate(m_xSpeed * deltatime, m_ySpeed * deltatime);
	m_transform->Rotate(0.10f * deltatime);*/
	if (Input.GetKeyDown(Keycode::UP))
	{
		m_transform->Translate(0, m_ySpeed * deltatime);
		if (curAnim != "Walk")
		{
			curAnim = "Walk";
			m_animator->ChangeState("Walk");
		}
	}
	else if (Input.GetKeyDown(Keycode::DOWN))
	{
		m_transform->Translate(0, -m_ySpeed * deltatime);
	}
	else if (Input.GetKeyDown(Keycode::RIGHT))
	{
		if (m_spriteRenderer->IsFlip())
			m_spriteRenderer->SetFlip(false);
		m_transform->Translate(m_xSpeed * deltatime, 0);
	}
	else if (Input.GetKeyDown(Keycode::LEFT))
	{
		if(!m_spriteRenderer->IsFlip())
			m_spriteRenderer->SetFlip(true);
		m_transform->Translate(-m_xSpeed * deltatime, 0);
	}
	else
	{
		if (curAnim != "Walk")
		{
			curAnim = "Walk";
			m_animator->ChangeState("Walk");
		}
	}

}

void PlayerController_Sample::OnTriggerEnter(Collider* other)
{
    //std::cout << "PlayerController::OnTriggerEnter: " << std::endl;


#ifdef _DEBUG
     std::cout << "PlayerController_Sample::OnTriggerEnter: " << other->GetOwner()->GetName() << std::endl;
#endif // !__DEBUG

}

void PlayerController_Sample::OnTriggerStay(Collider* other)
{
	#ifdef _DEBUG
	std::cout << "PlayerController_Sample::OnTriggerStay: " << other->GetOwner()->GetName() << std::endl;
#endif // !__DEBUG
}

void PlayerController_Sample::OnTriggerExit(Collider* other)
{
	#ifdef _DEBUG
	std::cout << "PlayerController_Sample::OnTriggerExit: " << other->GetOwner()->GetName() << std::endl;
#endif // !__DEBUG
}
