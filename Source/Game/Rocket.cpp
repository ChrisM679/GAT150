#include "Rocket.h"

FACTORY_REGISTER(Rocket)

void Rocket::Update(float dt)
{
	/*
	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(m_transform.rotation)) * speed;
	auto* rb = GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity = force * dt;
	}

	m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	Actor::Update(dt);
	*/
}

void Rocket::OnCollision(viper::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
	}
}