#include "EnginePCH.h"
#include "Core/StringHelper.h"

namespace viper {
	void EventManager::AddObserver(const Event::id_t& id, IObserver& observer) {
		m_observers[tolower(id)].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer) {
		IObserver* observerPtr = &observer;

		for (auto& eventType : m_observers) {
			auto& observers = eventType.second;

			std::erase_if(observers, [observerPtr](auto observer) 
				{ return observer == observerPtr; 
			});
		}
	}

	void EventManager::Notify(const Event& event) {
		auto it = m_observers.find(tolower(event.id));
		if (it != m_observers.end()) {
			auto& observers = it->second;
			for (auto observer : observers) {
				observer->OnNotify(event);
			}
		}
		else {
			Logger::Warning("could not find event {}", event.id);
		}
	}
}
