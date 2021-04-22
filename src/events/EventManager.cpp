#include "EventManager.h"


EventManager::EventManager() {
	eventQueue.reserve(20);
}


EventManager::~EventManager() { }


EventManager& EventManager::GetInstance(void) {
	static EventManager instance;	// guaranteed to be destroyed, lazy-loaded
	return instance;
}
