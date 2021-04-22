#pragma once
#include "Event.h"


class EventManager {
public:
	static EventManager& GetInstance(void);

	EventManager(EventManager& const) = delete;
	void operator=(EventManager& const) = delete;

private:
	EventManager() = default;


	// subscribe to (flags | flags | ...)
	// ...

};
