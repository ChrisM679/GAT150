#pragma once
#include "Framework/Actor.h"
#include "StringHelper.h"
#include "Singleton.h"
#include "Logger.h"
#include <map>
#include <memory>
#include <string>

#define FACTORY_REGISTER(classname) \
class Register##classname { \
    public: \
    Register##classname() { \
        viper::Factory::Instance().Register<classname>(#classname); \
    } \
}; \
Register##classname register_instance;

namespace viper {
	class CreatorBase {
		public:
			virtual ~CreatorBase() = default;
			virtual std::unique_ptr<Object> Create() = 0;
	};

	template<typename T>
		requires std::derived_from<T, Object>
	class Creator : public CreatorBase {
	public:
		std::unique_ptr<Object> Create() override {
			return std::make_unique<T>();
		}
	};

	template<typename T>
		requires std::derived_from<T, Object>
	class PrototypeCreator : public CreatorBase {
	public:
		PrototypeCreator(std::unique_ptr<T> prototype) : 
			m_prototype(std::move(prototype)) {}
		std::unique_ptr<Object> Create() override {
			return m_prototype->Clone();
		}

	private:
		std::unique_ptr<T> m_prototype;
	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template<typename T>
		requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

		template<typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);

		void RemoveAll() { m_registry.clear(); }

	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;
	};

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name) {
		std::string key = tolower(name);
		m_registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype) {
		std::string key = tolower(name);
		m_registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
	}

	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name) {
		std::string key = tolower(name);
		auto it = m_registry.find(key);
		if (it != m_registry.end()) {
			auto object = it ->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Factory: Created object of type '{}' but expected type '{}'", name, typeid(T).name());
		}
		else {
			Logger::Error("Factory: No creator registered for type '{}'", name);
		}

		return nullptr;
	}

	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name) {
		return Factory::Instance().Create<T>(name);
	}

	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const vec2& position, float rotation, float scale) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = Transform{ position, rotation, scale };
		return instance;
	}

	template<typename T = Actor>
		requires std::derived_from<T, Actor>
	std::unique_ptr<T> Instantiate(const std::string& name, const Transform& transform) {
		auto instance = Factory::Instance().Create<T>(name);
		instance->transform = transform;
		return instance;
	}
} 