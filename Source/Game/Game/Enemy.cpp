#include "../GamePCH.h"
#include "Enemy.h"
#include "Player.h"
#include "../Rocket.h"
#include "../GameData.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt)
{
	/*
	Actor* player = owner->m_scene->GetactorByName<Actor>("player");
	if (player)
	{
		viper::vec2 direction{ 0, 0 };
		direction = player->m_transform.position - owner->m_transform.position;
		direction = direction.Normalized();
		owner->m_transform.rotation = viper::math::radToDeg(direction.Angle());
	}

	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * speed;
	auto* rb = owner->GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	fireTimer -= dt;
	if (fireTimer <= 0) {
		fireTimer = fireTime;

		//std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 1.0f, 1.0f });

		viper::Transform m_transform{ owner->m_transform.position, owner->m_transform.rotation, 0.5f };
		auto rocket = std::make_unique<Actor>(m_transform);
		rocket->speed = 500.0f;
		rocket->owner->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->owner->tag = "enemy";

		//components
		auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		spriteRenderer->textureName = "textures/playership.png";
		rocket->AddComponent(std::move(spriteRenderer));

		auto rb = std::make_unique<viper::RigidBody>();
		rocket->AddComponent(std::move(rb));

		auto collider = std::make_unique<viper::CircleCollider2D>();
		collider->radius = 10.0f;
		rocket->AddComponent(std::move(collider));

		m_scene->AddActor(std::move(rocket));
	}

	Actor::Update(dt);
	*/
}
void Enemy::OnCollision(viper::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		owner->m_scene->GetGame()->AddPoints(100);
		viper::GetEngine().GetParticleSystem().EmitExplosion(owner->m_transform.position, 100, 10.0f, 200.0f, 2.0f);
		viper::GetEngine().GetParticleSystem().EmitExplosion(owner->m_transform.position, 50, 10.0f, 150.0f, 1.0f);
	}
}
