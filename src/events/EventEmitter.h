#pragma once
#include "EventBus.h"


class EventEmitter {
private:
	EventBus* bus;

public:
	EventEmitter(EventBus* const bus);
	virtual ~EventEmitter();

	void EmitEvent(Event* e);

};
