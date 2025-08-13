#pragma once
#include "Framework/Actor.h"

class Rocket : public viper::Actor {
public:
	float speed = 200.0f;

public:
	Rocket() = default;
	Rocket(const viper::Transform transform) :
		Actor{ transform }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};