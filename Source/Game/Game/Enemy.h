#pragma once
#include "Framework/Component.h"

class Enemy : public viper::Component {  
public:  
    float speed = 200.0f;  
    float fireTimer = 0.0f;  
    float fireTime = 0.0f;

public:  
    Enemy() = default;  

    void Update(float dt) override;
    void OnCollision(class viper::Actor* other);  
};