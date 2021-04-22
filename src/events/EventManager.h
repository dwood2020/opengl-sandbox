#pragma once
#include <vector>
#include "Event.h"


class EventManager {
private:
	std::vector<Event> eventQueue;

public:
	~EventManager();
	
	static EventManager& GetInstance(void);

	EventManager(EventManager&) = delete;
	void operator=(EventManager&) = delete;



private:
	EventManager();


	// subscribe to (flags | flags | ...)
	// ...

};
