#include "TilemapRenderer.h"
#include "Renderer/Tilemap.h"
#include "Engine.h"

namespace viper {
	FACTORY_REGISTER(TilemapRenderer)

	TilemapRenderer::TilemapRenderer(const TilemapRenderer& other) {
	}

	void TilemapRenderer::Start() {
		// Load the tilemap resource
		m_tilemap = Resources().Get<Tilemap>(m_tilemapName, GetEngine().GetRenderer());
		if (!m_tilemap) {
			Logger::Error("Could not load tilemap: {}", m_tilemapName);
			return;
		}
		
		// create physics bodies
		Transform transform;
		transform.scale = owner->m_transform.scale;
		transform.rotation = owner->m_transform.rotation;

		PhysicsBody::PhysicsBodyDef bodyDef;
		bodyDef.isDynamic = false;
		bodyDef.actor = owner;

		// iterate through layers
		for (auto layer : m_tilemap->GetLayers()) {

			if (!layer.hasCollision) continue;

			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = m_tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->m_transform.position + (m_tilemap->GetPosition(layer, i) * owner->m_transform.scale);

				transform.position = position;
				vec2 size = vec2{ source.w, source.h };

				auto physicsBody = std::make_unique<PhysicsBody>(transform, size, bodyDef, GetEngine().GetPhysics());
				m_physicsBodies.push_back(std::move(physicsBody));
			}
		}
	}

	void TilemapRenderer::Update(float dt) {
		//
	}

	void TilemapRenderer::Draw(Renderer& renderer) {
		// iterate through layers
		for (auto layer : m_tilemap->GetLayers()) {
			// get layer data (layout)
			for (int i = 0; i < layer.data.size(); i++) {
				int tileId = layer.data[i];
				if (tileId == 0) continue;

				rect source = m_tilemap->GetTextureRect(layer, tileId);
				vec2 position = owner->m_transform.position + (m_tilemap->GetPosition(layer, i) * owner->m_transform.scale);

				renderer.DrawTexture(*layer.texture, source, position.x, position.y, owner->m_transform.rotation, owner->m_transform.scale);
			}
		}
	}

	void TilemapRenderer::Read(const json::value_t& value) {
		Object::Read(value);

		JSON_READ_NAME(value, "tilemap_name", m_tilemapName);
	}
}