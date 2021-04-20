#include "Event.h"


Event::Event(eventtype::EventType type): type(type) { }


Event::Event(): Event(eventtype::NONE) { }


Event::~Event() { }


eventtype::EventType Event::GetType(void) const {
	return type;
}