#include "../GamePCH.h"
#include "Player.h"
#include "SpaceGame.h"
#include "../Rocket.h"
#include "../GameData.h"

FACTORY_REGISTER(Player)

void Player::Start() {
	m_rigidbody = owner->GetComponent<viper::RigidBody>();
}

void Player::Update(float dt)
{
    
    viper::Particle partical;
	partical.position = owner->m_transform.position;
    partical.velocity = viper::vec2{ viper::random::getReal(-200.0f , 200.0f), viper::random::getReal(-200.0f , 200.0f) };
	partical.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
	partical.lifespan = 2.0f;
	viper::GetEngine().GetParticleSystem().AddParticle(partical);

    //Rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

    owner->m_transform.rotation += (rotate * rotationRate) * dt;

	//Thrust
	float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->m_transform.rotation)) * thrust * speed;
    auto* rb = owner->GetComponent<viper::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

	owner->m_transform.position.x = viper::math::wrap(owner->m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    owner->m_transform.position.y = viper::math::wrap(owner->m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

    /*
	fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && fireTimer <=0 ) {
		fireTimer = fireTime;

		auto sound = viper::Resources().Get<viper::AudioClip>("bass.wav", viper::GetEngine().GetAudio()).get();
        if (sound) {
            viper::GetEngine().GetAudio().PlaySound(*sound);
        }
        
        viper::Transform m_transform{ this->m_transform.position, this->m_transform.rotation, 0.5f };
        auto rocket = std::make_unique<Rocket>(m_transform);
        rocket->speed = 1500.0f;
		rocket->lifespan = 1.0f;
        rocket->name = "rocket";
        rocket->tag = "player";

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

void Player::OnCollision(viper::Actor* other)
{
    if (owner->tag == "enemy") {
        viper::GetEngine().GetParticleSystem().EmitExplosion(owner->m_transform.position, 150, 10.0f, 250.0f, 2.0f);
        viper::GetEngine().GetParticleSystem().EmitExplosion(owner->m_transform.position, 100, 10.0f, 200.0f, 2.0f);
        owner->destroyed = true;
    }

    if (owner->tag != other->tag) {
        owner->destroyed = true;
        dynamic_cast<SpaceGame*>(owner->m_scene->GetGame())->OnPlayerDeath();
    }
}

void Player::Read(const viper::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, rotationRate);
	JSON_READ(value, fireTime);
}
