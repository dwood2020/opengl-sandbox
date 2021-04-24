#include "EventBus.h"
#include "EventEmitter.hpp"


EventBus::EventBus() { }


EventBus::~EventBus() { }


void EventBus::AddListener(EventType type, std::function<void(Event&)> callback) {

	auto it = listeners.find(type);

	if (it == listeners.end()) {		
		std::vector<std::function<void(Event&)>> vec;
		vec.push_back(callback);

		listeners.insert(std::pair<EventType, std::vector<std::function<void(Event&)>>>(type, vec));
	}
	else {
		it->second.push_back(callback);
	}


}


void EventBus::SendEvent(Event& e) {
	eventQueue.push_back(e);
}


void EventBus::Poll(void) {	

	for (Event& e : eventQueue) {
		auto it = listeners.find(e.GetType());
		
		if (it != listeners.end()) {
			for (std::function<void(Event&)> callback : it->second) {
				callback(e);
			}
		}
	}

	eventQueue.clear();	//TODO: don't delete events which are not processed?
}
