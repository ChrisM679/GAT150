#pragma once
#include "Framework/Actor.h"

class Player : public viper::Actor {
public:
	float speed = 200;
	float rotationRate = 180;
	float fireTime = 0.2f;
	float fireTimer = 0;

public:
	Player() = default;
	Player(const viper::Transform transform, std::shared_ptr<viper::Model> model) :
		Actor{ transform, model }
	{}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};