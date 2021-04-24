#include "EventBus.h"


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
