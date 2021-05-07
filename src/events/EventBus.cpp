#include "EventBus.h"
#include "EventEmitter.hpp"
#include "EventListener.hpp"


EventBus::EventBus() { }


EventBus::~EventBus() { }


void EventBus::AddListener(EventType type, EventListener* listener) {

	auto it = listeners.find(type);

	if (it == listeners.end()) {
		std::vector<EventListener*> vec;
		vec.push_back(listener);

		listeners.insert(std::pair<EventType, std::vector<EventListener*>>(type, vec));
	}
	else {
		it->second.push_back(listener);
	}

}


void EventBus::SendEvent(Event& e) {
	eventQueue.push_back(e);
}


void EventBus::Poll(void) {	

	for (Event& e : eventQueue) {
		auto it = listeners.find(e.GetType());

		if (it != listeners.end()) {
			for (EventListener* listener : it->second) {
				listener->OnEvent(e);
			}
		}
	}

	eventQueue.clear();	//TODO: don't delete events which are not processed?
}
