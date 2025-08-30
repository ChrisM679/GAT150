#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {

}

void EnemyController::Update(float dt) {
	
}

void EnemyController::OnCollision(viper::Actor* other) {
}

void EnemyController::OnNotify(const viper::Event& event)
{

}

void EnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
