#include "Actor.h"
#include "../Renderer/Model.h"

namespace viper
{
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0.0f) {
			lifespan -= dt;
			if (lifespan <= 0.0f) {
				destroyed = true;
				return;
			}
		}

		m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping) * dt);
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		m_model->Draw(renderer, m_transform);
	}

	float Actor::GetRadius()
	{
		return (m_model) ? m_model->GetRadius() * m_transform.scale * 0.9f : 0.0f;
	}

}
