#include "Enemy.h"
#include "Player.h"
#include "../Rocket.h"
#include "../GameData.h"

void Enemy::Update(float dt)
{
	Actor* player = m_scene->GetactorByName("player");
	if (player)
	{
		viper::vec2 direction{ 0, 0 };
		direction = player->m_transform.position - m_transform.position;
		direction = direction.Normalized();
		m_transform.rotation = viper::math::radToDeg(direction.Angle());
	}

	viper::vec2 force = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(m_transform.rotation)) * speed;
	auto* rb = GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	fireTimer -= dt;
	if (fireTimer <= 0) {
		fireTimer = fireTime;

		//std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 1.0f, 1.0f });

		viper::Transform m_transform{ this->m_transform.position, this->m_transform.rotation, 0.5f };
		auto rocket = std::make_unique<Rocket>(m_transform);
		rocket->speed = 500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy";

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
}

void Enemy::OnCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true;
		m_scene->GetGame()->AddPoints(100);
		viper::GetEngine().GetParticleSystem().EmitExplosion(m_transform.position, 100, 10.0f, 200.0f, 2.0f);
		viper::GetEngine().GetParticleSystem().EmitExplosion(other->m_transform.position, 50, 10.0f, 150.0f, 1.0f);
	}
}
