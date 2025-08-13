#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"

namespace viper {

	void SpriteRenderer::Update(float dt) {\
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer) {
		auto texture = Resources().Get<Texture>(textureName, renderer).get();
			if (texture) {
				renderer.DrawTexture(*texture,
					owner->m_transform.position.x,
					owner->m_transform.position.y,
					owner->m_transform.rotation,
					owner->m_transform.scale);
			}
	}
}