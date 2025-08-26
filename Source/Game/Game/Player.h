#pragma once
#include "Framework/Component.h"

class Player : public viper::Component, public viper::ICollidable {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0;

	viper::RigidBody* m_rigidbody{ nullptr };

public:
	Player() = default;

	CLASS_PROTOTYPE(Player)

	void Start() override;
	void Update(float dt) override;
	void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
};