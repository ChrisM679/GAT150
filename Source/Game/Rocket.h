#pragma once
#include "Framework/Component.h"

class Rocket : public viper::Component, public viper::ICollidable {
public:
	float speed = 200.0f;

public:
	Rocket() = default;

	CLASS_PROTOTYPE(Rocket)

	void Update(float dt) override;
	void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
};