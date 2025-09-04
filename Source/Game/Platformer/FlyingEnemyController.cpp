#include "FlyingEnemyController.h"

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	m_rigidbody = owner->GetComponent<viper::RigidBody>();
}

void FlyingEnemyController::Update(float dt) {

	auto player = owner->m_scene->GetActorByName<viper::Actor>("platformplayer");
	if (player) {
		viper::vec2 direction = player->m_transform.position - owner->m_transform.position;
		m_rigidbody->ApplyForce(direction);
	}
}

void FlyingEnemyController::OnCollision(viper::Actor* other) {

}

void FlyingEnemyController::OnNotify(const viper::Event& event) {

}

void FlyingEnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
