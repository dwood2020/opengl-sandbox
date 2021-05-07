#pragma once
#include <map>
#include <vector>
#include <functional>
#include "Event.hpp"


class EventEmitter;
class EventListener;


class EventBus final {
private:
	std::vector<Event> eventQueue;	
	std::map<EventType, std::vector<EventListener*>, std::less<EventType>> listeners;

public:
	EventBus();
	~EventBus();
	
	void AddListener(EventType type, EventListener* listener);	

	void Poll(void);

private:
	void SendEvent(Event& e);

	friend class EventEmitter;
};