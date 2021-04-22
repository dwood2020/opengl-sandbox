#include "EventManager.h"

EventManager& EventManager::GetInstance(void) {
	static EventManager instance;	// guaranteed to be destroyed, lazy-loaded
	return instance;
}
