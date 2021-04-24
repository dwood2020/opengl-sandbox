#include "Event.h"


Event::Event(EventType type): type(type) { }


Event::~Event(){ }


const EventType& Event::GetType(void) const {
	return type;
}
