#pragma once
#include "Components/RendererComponent.h"

namespace viper {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;

		CLASS_PROTOTYPE(MeshRenderer)

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
	};
}