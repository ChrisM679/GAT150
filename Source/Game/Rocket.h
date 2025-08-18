#pragma once
#include "Framework/Component.h"

class Rocket : public viper::Component {
public:
	float speed = 200.0f;

public:
	Rocket() = default;
	//Rocket(const viper::Transform transform) :
	//	Actor{ transform }
	//{}

	void Update(float dt) override;

	void OnCollision(class Actor* other);
};