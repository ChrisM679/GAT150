#pragma once

#include "Framework/Actor.h"

class Enemy : public viper::Actor {
public:
	float speed = 200.0f;
	float fireTimer = 0.0f;
	float fireTime = 0.0f;

public:
	Enemy() = default;
	Enemy(const viper::Transform transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture }
	{
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};