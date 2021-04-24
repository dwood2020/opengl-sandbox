#include "EventListener.h"


EventListener::EventListener(): listenerId(0), bus(nullptr) { }


EventListener::~EventListener() {
	if (bus != nullptr) {
		bus->Unsubscribe(this);
	}
}
