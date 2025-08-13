#include "ParticleSystem.h"
#include "Renderer.h"

namespace viper {
	bool ParticleSystem::Initialize(int poolSize) {
		m_particles.resize(poolSize);

		return true;
	}

	void ParticleSystem::Shutdown() {
		m_particles.clear();
	}

	void ParticleSystem::Update(float dt) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				particle.lifespan -= dt;
				if (particle.lifespan <= 0.0f) {
					particle.active = false;
					continue;
				}
				particle.position += particle.velocity * dt;
			}
		}
	}

	void ParticleSystem::Draw(class Renderer& renderer) {
		for (const auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}

	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* Particle = GetFreeParticle();
		if (Particle) {
			*Particle = particle;
			Particle->active = true;
		}
	}

	Particle* ParticleSystem::GetFreeParticle() {
		for (auto& particle : m_particles) {
			if (!particle.active) {
				return &particle;
			}
		}
		return nullptr;
	}

	void ParticleSystem::EmitExplosion(const vec2& position, int count, float minSpeed, float maxSpeed, float lifespan)
	{
		for (int i = 0; i < count; ++i) {
			Particle p;
			
			p.velocity = random::onUnitCircle() * random::getReal(minSpeed, maxSpeed);
			p.position = position;

			float t = random::getReal(0.0f, 1.0f);
			if (t < 0.5f) {
				float inner = t / 0.5f;
				p.color = vec3{ 1.0f, 0.2f + 0.6f * inner, 0.0f };
			}
			else {
				float inner = (t - 0.5f) / 0.5f;
				p.color = vec3{ 1.0f, 0.8f + 0.2f * inner, 0.0f };
			}

			if (random::getReal() < 0.05f) {
				p.color = vec3{ 1.0f, 1.0f, 1.0f };
			}

			p.lifespan = lifespan;
			p.active = true;

			AddParticle(p);
		}
	}

}
