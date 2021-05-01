#pragma once
#include <map>
#include <vector>
#include <functional>
#include "Event.hpp"


class EventEmitter;
class EventListener;

//TODO: BUild OOP EventListener class!!
// see comment below

class EventBus final {
private:
	std::vector<Event> eventQueue;
	std::map<EventType, std::vector<std::function<void(Event&)>>, std::less<EventType>> listeners;

public:
	EventBus();
	~EventBus();

	void AddListener(EventType type, std::function<void(Event&)> callback);

	//TODO: Add class-type listeners!!

	void Poll(void);

private:
	void SendEvent(Event& e);

	friend class EventEmitter;
};