#pragma once
#include "EventBus.h"


/// <summary>
/// This class provides the interface for any class which shall emit events (of any type).
/// </summary>
class EventEmitter {
protected:
	EventBus* bus;

public:
	/// <summary>
	/// Constructor. Takes the EventBus as input.
	/// </summary>
	/// <param name="bus">Event bus</param>
	EventEmitter(EventBus* bus): bus(bus) { }

	virtual ~EventEmitter() { }


	/// <summary>
	/// Emits an event onto the event bus.
	/// </summary>
	/// <param name="e">Event to be emitted</param>
	void EmitEvent(Event& e) {
		bus->SendEvent(e);
	}
};
