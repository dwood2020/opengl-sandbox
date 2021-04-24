#include "EventEmitter.h"

EventEmitter::EventEmitter(EventBus* const bus) {
	this->bus = bus;
}


EventEmitter::~EventEmitter() { }


void EventEmitter::EmitEvent(Event* e) {
	bus->SendEvent(e);
}
