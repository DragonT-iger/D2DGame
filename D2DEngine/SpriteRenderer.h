#pragma once  
#include "Component.h"  
#include "GameObject.h"

class D2DRenderer;

class SpriteRenderer : public MonoBehaviour  
{  
public:  
    SpriteRenderer() = default;
    virtual ~SpriteRenderer() = default;  

    virtual void Awake() override { m_transform = GetOwner()->GetComponent<Transform>(); }

    void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap) { m_bitmap = bitmap; }  //�⺻ ��������Ʈ ����
	void SetDestRect(const D2D1_RECT_F& rect) { m_destRect = rect; }    //�ִϸ��̼��̸� ����� �κ� ����


    void Render(D2DRenderer* renderer, const D2D1::Matrix3x2F& viewTM);

private:  
    
    Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;  
    D2D1_RECT_F                                                m_destRect; //��������Ʈ ũ��� �Ȱ��ƾ���
	Transform*                                  m_transform = nullptr;
};
