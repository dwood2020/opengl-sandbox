#include "Event.h"


Event::Event(EventType type): type(type) { }


Event::Event(): Event(eventtype::NONE) { }


Event::~Event() { }


EventType Event::GetType(void) const {
	return type;	
}