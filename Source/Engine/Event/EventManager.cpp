#include "EnginePCH.h"
#include "Core/StringHelper.h"

namespace viper {
	void EventManager::AddObserver(const Event::id_t& eventID, IObserver* observer) {
		m_observers[tolower(id)].push_back(observer);
	}

	void EventManager::RemoveObserver(IObserver* observer) {
		IObserver* observerPtr = observer;

		for (auto& eventType : m_observers) {
			auto observers = eventType.second;

			std::erase_if(observers, [observerPtr](auto& observer) 
				{ return observer == observerPtr; 
			});
		}
	}

	void EventManager::Notify(const Event& event) {
		auto iter = m_observers.find(event.id);
		if (iter != m_observers.end()) {
			for (auto observer : iter->second) {
				observer->OnNotify();
			}
		}
	}
}
