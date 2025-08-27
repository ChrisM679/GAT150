#include "Observer.h"

namespace viper {
	viper::IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}