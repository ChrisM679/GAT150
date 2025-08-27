#pragma once
#include "Framework/Component.h"

namespace viper {
	class RigidBody : public Component {
	public:
		PhysicsBody::PhysicsBodyDef bodyDef;
		vec2 size{ 0, 0 };

		vec2 velocity{ 0, 0 };
		float damping{ 0 };

	public:
		RigidBody() = default;
		RigidBody(const RigidBody& other);

		CLASS_PROTOTYPE(RigidBody)

		void Start() override;
		void Update(float dt) override;
		void Read(const json::value_t& value) override;

		void ApplyForce(const vec2& force);
		void ApplyTorque(float radians);

		void SetLinearVelocity(const vec2& velocity);

	private:
		std::unique_ptr<PhysicsBody> m_physicsBody;
	};
}