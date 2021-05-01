#pragma once
#include "Event.hpp"
#include "EventBus.h"


class EventListener {
public:
	EventListener() { };
	virtual ~EventListener() { }

protected:
	virtual void OnEvent(Event& e) { };

	friend class EventBus;

};