#include "EventBus.h"
#include "EventListener.h"


EventBus::EventBus() {
	eventQueue.reserve(20);
}


EventBus::~EventBus() { }


void EventBus::Subscribe(EventListener& self, std::function<void(Event&)> callback, EventType typeFlags) {
	if (self.listenerId == 0) {
		// generate new id
		self.listenerId = GetListenerId();
	}

	ListenerRef ref;
	ref.typeFlags = typeFlags;
	ref.callback = callback;

	listeners.insert(std::pair<unsigned int, ListenerRef>(self.listenerId, ref));
}


void EventBus::Unsubscribe(const EventListener* self) {
	//TODO: implement
}


void EventBus::Poll(void) const {
	for (auto eventIt = eventQueue.begin(); eventIt != eventQueue.end(); ++eventIt) {

		for (auto listenerIt = listeners.begin(); listenerIt != listeners.end(); ++listenerIt) {
			if (listenerIt->second.typeFlags & eventIt->GetType()) {

			}
		}

	}
}


unsigned int EventBus::GetListenerId(void) {
	if (!listeners.empty()) {
		return listeners.rbegin()->first + 1u;
	}
	else {
		return 1u;
	}
}
