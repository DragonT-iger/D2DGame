#pragma once
/// 날짜 / 이름 / 수정내용
/// 2025-07-02 권용범 최초버전 작성

/// <summary>
/// 라이프 사이클을 관리하는 MonoBehaviour 클래스
/// </summary>
class MonoBehaviour : public Behaviour {
public:
    virtual ~MonoBehaviour() = default;

    virtual void Awake() {}                            
    virtual void Start() {}                             
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float fixedDelta) = 0;
	virtual void LateUpdate(float deltaTime) = 0;
};