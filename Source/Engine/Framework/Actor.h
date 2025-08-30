#pragma once
#include "Object.h"
#include "Component.h"
#include "Math/Transform.h"
#include "Renderer/Texture.h"

#include <string>
#include <memory>
#include <vector>

namespace viper {
	class Actor : public Object {
	public:
		std::string tag;

		bool destroyed{ false };
		float lifespan{ 0.0f };
		bool persistent{ false };

		Transform m_transform;
		class Scene* m_scene{ nullptr };

	public:
		Actor() = default;
		Actor(const Transform transform) :
			m_transform{ transform }
		{}
		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		void Read(const json::value_t& value) override;

		virtual void Start();
		virtual void Destroyed();

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
			return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}
