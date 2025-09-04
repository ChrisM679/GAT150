#include "Scene.h"
#include "Renderer/Renderer.h"
#include "Components/ColliderComponent.h"

namespace viper
{
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="dt">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}

		std::erase_if(m_actors, [](auto& actor)
		{
			return (actor->destroyed);
		});

		/*for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}*/
		/*
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {

				continue;

				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}

			}
		}
		*/
	}
	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor.
	/// </summary>
	/// <param name="m_actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start) {
		actor->m_scene = this;
		if (start) actor->Start();
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force) {
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if (!(*iter)->persistent || force) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	bool Scene::Load(const std::string& sceneName) {
		viper::json::document_t document;
		if (!viper::json::Load(sceneName, document)) {
			viper::Logger::Error("Failed to load scene: {}", sceneName);
			return false;
		}
		Read(document);
		for (auto& actor : m_actors) {
			actor->Start();
		}

		return true;
	}


	void Scene::Read(const json::value_t& value) {
		//Read Prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		//Read Actor
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}
}