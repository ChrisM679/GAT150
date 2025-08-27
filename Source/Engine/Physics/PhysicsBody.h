#pragma once
#include <box2d/box2d.h>

namespace viper {
	class PhysicsBody {
	public:
		enum class Shape {
			Box,
			Circle,
			Capsule
		};
		struct PhysicsBodyDef {
			// body
			float gravityScale = 1;
			float linearDamping = 0.2f;
			float angularDamping = 0.2f;
			bool  constrainAngle = false;
			bool  isDynamic = true;

			// material
			float friction = 0.3f;
			float restitution = 0.5f;
			float density = 1.0f;

			// shape
			Shape shape = Shape::Box;
			bool isSensor = false;

			class Actor* actor{ nullptr };
		};
		PhysicsBody(const Transform& transform, const vec2& size, const PhysicsBodyDef& def, const class Physics& physics);
		~PhysicsBody();

		vec2 GetPosition();
		float GetAngle();

		void ApplyForce(const vec2& force);
		void ApplyTorque(float radians);

		void SetLinearVelocity(const vec2& velocity);

	private:
		b2BodyId m_bodyId{ b2_nullBodyId };
	};
}
