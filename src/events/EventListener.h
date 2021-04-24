#pragma once
#include "Event.h"
#include "EventBus.h"


class EventListener {
private:
	unsigned int listenerId;	
	EventBus* bus;

	friend class EventBus;

public:
	EventListener();
	virtual ~EventListener();

	virtual void OnEvent(Event& e) = 0;
	
};

