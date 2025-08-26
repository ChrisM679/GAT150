#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(SpriteRenderer)
	
	void SpriteRenderer::Start() {
		texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
	}

	void SpriteRenderer::Update(float dt) {\
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer) {
		auto texture = Resources().Get<Texture>(textureName, renderer);
			if (texture) {
				renderer.DrawTexture(*texture,
					owner->m_transform.position.x,
					owner->m_transform.position.y,
					owner->m_transform.rotation,
					owner->m_transform.scale);
			}
	}
	void SpriteRenderer::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ_NAME(value, "texture_name", textureName);
	}
}