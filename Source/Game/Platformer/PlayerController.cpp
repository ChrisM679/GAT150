#include "PlayerController.h"

FACTORY_REGISTER(PlayerController)

void PlayerController::Start() {

}

void PlayerController::Update(float dt) {
	float dir = 0;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) { dir -= 1; }
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) { dir += 1; }

	if (dir != 0) {
		m_rigidbody->ApplyForce(viper::vec2{ 1 , 0 } * dir * 1000);
	}

	if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidbody->ApplyForce(viper::vec2{ 0, -1 } * 10000);
	}
}

void PlayerController::OnCollision(viper::Actor* other) {

}

void PlayerController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
