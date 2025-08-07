#include "Actor.h"
#include "Renderer/Renderer.h"

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

			renderer.DrawTexture(m_texture.get(), m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
	}

	float Actor::GetRadius()
	{
		return (m_texture) ? (m_texture->GetSize().Length() * 0.5f) * m_transform.scale * 0.9f : 0.0f;
	}

}
