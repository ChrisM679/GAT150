#include "EnemyController.h"

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	m_rigidbody = owner->GetComponent<viper::RigidBody>();
}

void EnemyController::Update(float dt) {
	float dir = 0;
	
	auto player = owner->m_scene->GetActorByName<viper::Actor>("platformplayer");
	if (player) {
		if (player->m_transform.position.x < owner->m_transform.position.x) {
			dir = -1;
		}
		else {
			dir = 1;
		}
	}

	if (dir != 0) {
		m_rigidbody->ApplyForce(viper::vec2{ 1 , 0 } *dir * 1000);
	}
}

void EnemyController::OnCollision(viper::Actor* other) {

}

void EnemyController::OnNotify(const viper::Event& event) {

}

void EnemyController::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, fireTime);
}
