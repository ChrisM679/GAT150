#include "RigidBody.h"

namespace viper {

	void viper::RigidBody::Update(float dt) {
		owner->m_transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}
}