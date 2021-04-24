#pragma once
#include <map>
#include <vector>
#include <functional>
#include "Event.h"


class EventBus final {
private:
	std::vector<Event> eventQueue;
	std::map<EventType, std::vector<std::function<void(Event&)>>, std::less<EventType>> listeners;

public:
	EventBus();
	~EventBus();

	void AddListener(EventType type, std::function<void(Event&)> callback);

	void SendEvent(Event& e);

	void Poll(void);

};