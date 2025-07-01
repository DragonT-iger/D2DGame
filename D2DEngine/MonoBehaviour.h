#pragma once

#include "pch.h"


class MonoBehaviour : public Behaviour {
public:
    virtual ~MonoBehaviour() = default;

    virtual void Awake() {}                            
    virtual void Start() {}                             
	virtual void Update(float deltaTime) = 0;
	virtual void FixedUpdate(float fixedDelta) = 0;
	virtual void LateUpdate(float deltaTime) = 0;
};