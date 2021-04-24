#pragma once
#include <vector>
#include <map>
#include <functional>
#include "Event.h"


class EventListener;


class EventBus final {
private:
	struct ListenerRef {
		EventType typeFlags = EventType::NONE;
		std::function<void(Event&)> callback;
	};

	std::vector<Event> eventQueue;
	std::multimap<unsigned int, ListenerRef, std::less<unsigned int>> listeners;
	

public:
	EventBus();
	~EventBus();

	void Subscribe(EventListener& self, std::function<void(Event&)> callback, EventType typeFlags);
	void Unsubscribe(const EventListener* self);

	void Poll(void) const;

private:
	unsigned int GetListenerId(void);

};
