#pragma once
#include "EventBus.h"


class EventEmitter {
private:
	EventBus* bus;

public:
	EventEmitter(const EventBus* bus);
	virtual ~EventEmitter();


};
