#include "Event.h"


Event::Event(): type(eventtype::NONE) { }


Event::Event(eventtype::EventType type): type(type) { }


Event::~Event() { }


eventtype::EventType Event::GetType(void) const {
	return type;
}