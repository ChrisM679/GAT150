#pragma once
#include "Core/StringHelper.h"
#include "Core/Serializable.h"
#include <string>
#include <vector>
#include <list>
#include <memory>

namespace viper {
	class Actor;
	class Game;

	class Scene : public ISerializable {
	public:
		Scene(Game* game) : m_game{ game } {}

		bool Load(const std::string& sceneName);
		void Read(const json::value_t& value) override;

		void Update(float dt);
		void Draw(class Renderer& renderer);
			
		void AddActor(std::unique_ptr<Actor> actor, bool start = true);
		void RemoveAllActors(bool force = false);

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		class Game* m_game{ nullptr };
		std::list<std::unique_ptr<Actor>> m_actors;
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (toLower(actor->name) == toLower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag) {
		std::vector<T*> results;
		for (auto& actor : m_actors) {
			if (toLower(actor->tag) == toLower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}
		return results;
	}
}