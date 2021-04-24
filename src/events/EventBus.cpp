#include "EventBus.h"
#include "EventListener.h"


EventBus::EventBus() {
	eventQueue.reserve(20);
}


EventBus::~EventBus() { }


void EventBus::Subscribe(EventListener* self, std::function<void(const Event&)> callback, EventType typeFlags) {
	if (self->listenerId == 0) {
		// generate new id
		self->listenerId = GetListenerId();
	}

	ListenerRef ref;
	ref.typeFlags = typeFlags;
	ref.callback = callback;

	listeners.insert(std::pair<unsigned int, ListenerRef>(self->listenerId, ref));
}


void EventBus::Unsubscribe(const EventListener* self) {
	//TODO: implement
}


void EventBus::Poll(void) {	
	for (unsigned int i = 0; i < eventQueue.size(); i++) {
		for (auto it = listeners.begin(); it != listeners.end(); ++it) {
			if (it->second.typeFlags & eventQueue[i].GetType()) {
				it->second.callback(eventQueue[i]);
			}
		}
	}
	
	eventQueue.clear();
}


unsigned int EventBus::GetListenerId(void) {
	if (!listeners.empty()) {
		return listeners.rbegin()->first + 1u;
	}
	else {
		return 1u;
	}
}
