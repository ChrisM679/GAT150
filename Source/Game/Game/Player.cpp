#include "Player.h"
#include "Engine.h"
#include "SpaceGame.h"
#include "../Rocket.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Math/Vector3.h"
#include "Core/Random.h"
#include "../GameData.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

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
    velocity += force;

	m_transform.position.x = viper::math::wrap(m_transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
    m_transform.position.y = viper::math::wrap(m_transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	fireTimer -= dt;
    if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && fireTimer <=0 ) {
		fireTimer = fireTime;

        std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 1.0f, 1.0f, 1.0f });

        viper::Transform m_transform{ this->m_transform.position, this->m_transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(m_transform, viper::Resources().Get<viper::Texture>("textures/playership.png", viper::GetEngine().GetRenderer()));
        rocket->speed = 1500.0f;
		rocket->lifespan = 1.0f;
        rocket->name = "rocket";
        rocket->tag = "player";

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
