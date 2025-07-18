#pragma once  
#include "Component.h"  
#include "GameObject.h"

class D2DRenderer;

class SpriteRenderer : public MonoBehaviour  
{  
public:  

    SpriteRenderer() = default;
    virtual ~SpriteRenderer() = default;

    virtual void Awake() override { m_transform = GetComponent<Transform>(); } // this 참조로 바꿨음

    void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap) { m_bitmap = bitmap; }  //기본 스프라이트 설정
    void SetSize(float width, float height);


    void Render(const D2D1::Matrix3x2F& viewTM);

private:  
    
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap ;  
    D2D1_RECT_F                                                m_destRect; //스프라이트 크기랑 똑같아야함
	Transform*                                  m_transform = nullptr;
};
