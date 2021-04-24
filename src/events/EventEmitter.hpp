#pragma once
#include "EventBus.h"


class EventEmitter {
protected:
	EventBus* bus;

public:
	EventEmitter(EventBus* bus): bus(bus) { }

	virtual ~EventEmitter() { }

	void OnEvent(Event& e) {
		bus->SendEvent(e);
	}
};
