#pragma once
#include "Event.hpp"


enum class WindowEventType : EventType_t {
	WindowClose = static_cast<EventType_t>(EventType::WindowClose),
};

//TODO: Move Window events here