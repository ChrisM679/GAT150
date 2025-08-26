#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"

namespace viper {
	FACTORY_REGISTER(Actor)
	void Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan > 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		for (auto& component : m_components) {
			if (component->active) {
				component->Update(dt);
			}
		}
	}

	void Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		for (auto& component : m_components) {
			if (component->active) {
				auto rendererCompomet = dynamic_cast<RendererComponent*>(component.get());
				if (rendererCompomet) {
					rendererCompomet->Draw(renderer);
				}
			}
		}
	}

	void Actor::OnCollision(Actor* other) {
		auto collidables = GetComponents<ICollidable>();
		for (auto collidable : collidables) {
			collidable->OnCollision(other);
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		m_components.push_back(std::move(component));
	}

	Actor::Actor(const Actor& other) : 
		Object(other),
		tag(other.tag),
		destroyed(other.destroyed),
		lifespan(other.lifespan)
	{
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}

	void Actor::Read(const json::value_t& value) {
		Object::Read(value);
		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);
		if (JSON_HAS(value, m_transform)) m_transform.Read(JSON_GET(value, m_transform));

		// Read Components
		if (JSON_HAS(value, m_components)) {
			for (auto& componentValue : JSON_GET(value, m_components).GetArray()) {

				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}

	void Actor::Start() {
		for (auto& component : m_components) {
			component->Start();
		}
	}

	void Actor::Destroyed() {
		for (auto& component : m_components) {
			component->Destroyed();
		}
	}

}
