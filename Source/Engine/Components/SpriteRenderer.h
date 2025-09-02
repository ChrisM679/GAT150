#pragma once
#include "RendererComponent.h"

namespace viper {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
		rect textureRect;
		res_t<Texture> texture;

		CLASS_PROTOTYPE(SpriteRenderer)

		void Start() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}