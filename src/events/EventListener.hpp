#pragma once
#include "Event.hpp"
#include "EventBus.h"


class EventListener {
public:
	EventListener() = default;
	virtual ~EventListener() { }

protected:
	virtual void OnEvent(Event& e) = 0;

	friend class EventBus;

};