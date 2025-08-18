#include "../GamePCH.h"
#include "Player.h"
#include "SpaceGame.h"
#include "../Rocket.h"
#include "../GameData.h"

FACTORY_REGISTER(Player)

void Player::Update(float dt)
{
    viper::Particle partical;
	partical.position = m_transform.position;
    partical.velocity = viper::vec2{ viper::random::getReal(-200.0f , 200.0f), viper::random::getReal(-200.0f , 200.0f) };
	partical.color = viper::vec3{ 1.0f, 1.0f, 1.0f };
	partical.lifespan = 2.0f;
	//viper::GetEngine().GetParticleSystem().AddParticle(partical);

    //Rotation
    float rotate = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	m_transform.rotation += (rotate * rotationRate) * dt;

	//Thrust
	float thrust = 0;
    if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

    viper::vec2 direction{ 1, 0 };
	viper::vec2 force = direction.Rotate(viper::math::degToRad(m_transform.rotation)) * thrust * speed;
    auto* rb = GetComponent<viper::RigidBody>();
    if (rb) {
        rb->velocity += force * dt;
    }

	m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

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

}

void Player::OnCollision(Actor* other)
{
    if (other->tag == "enemy") {
        viper::GetEngine().GetParticleSystem().EmitExplosion(m_transform.position, 150, 10.0f, 250.0f, 2.0f);
        viper::GetEngine().GetParticleSystem().EmitExplosion(other->m_transform.position, 100, 10.0f, 200.0f, 2.0f);
        other->destroyed = true;
    }

    if (tag != other->tag) {
        destroyed = true;
        dynamic_cast<SpaceGame*>(m_scene->GetGame())->OnPlayerDeath();
    }
}
