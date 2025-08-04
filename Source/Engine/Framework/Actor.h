#pragma once
#include "../Math/Transform.h"

#include <string>
#include <memory>

namespace viper {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.0f };

		bool destroyed{ false };
		float lifespan{ 0.0f };

		Transform m_transform;
		class Scene* m_scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform transform, std::shared_ptr<class Model> model) :
			m_transform{ transform } ,
			m_model{ model }
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

	protected:
		std::shared_ptr<Model> m_model;
	};
}
