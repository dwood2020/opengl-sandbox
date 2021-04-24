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
		std::function<void(const Event&)> callback;
	};

	std::vector<Event*> eventQueue;
	std::multimap<unsigned int, ListenerRef, std::less<unsigned int>> listeners;
	

public:
	EventBus();
	~EventBus();

	void Subscribe(EventListener* self, std::function<void(const Event&)> callback, EventType typeFlags);
	void Unsubscribe(const EventListener* self);

	void SendEvent(Event* e);

	void Poll(void);

private:
	unsigned int GetListenerId(void);

};
