#pragma once
#include "Components/RigidBody.h"
#include "Physics/Collidable.h"
#include "Event/Observer.h"
#include "Event/Event.h"

class FlyingEnemyController : public viper::Component, public viper::ICollidable, public viper::IObserver {
public:
    float speed = 0;
    float maxSpeed = 0;
    float jump = 0;
    float fireTimer = 0;
    float fireTime = 0;

    viper::RigidBody* m_rigidbody{ nullptr };

public:
    FlyingEnemyController() = default;

    CLASS_PROTOTYPE(FlyingEnemyController)

    void Start() override;
    void Update(float dt) override;
    void OnCollision(class viper::Actor* other) override;

    void OnNotify(const viper::Event& event) override;

    void Read(const viper::json::value_t& value) override;
};