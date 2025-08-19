#include "EnginePCH.h"
#include "MeshRenderer.h"
#include <Renderer/Mesh.h>

namespace viper {

	void viper::MeshRenderer::Update(float dt) {
		//
	}

	void viper::MeshRenderer::Draw(Renderer& renderer) {
		auto mesh = Resources().Get<Mesh>(meshName);
		if (mesh) {
			mesh->Draw(renderer, owner->m_transform);
		}
	}
}
