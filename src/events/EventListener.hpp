#pragma once
#include "Event.hpp"
#include "EventBus.h"


/// <summary>
/// This class provides the interface for any class which shall 
/// act as event listener.
/// </summary>
class EventListener {
public:
	/// <summary>
	/// Constructor.
	/// </summary>
	EventListener() { }

	virtual ~EventListener() { }

protected:
	/// <summary>
	/// Event processing method. 
	/// This must be implemented once. If this listener was added to listen
	/// to multiple event types, an event type differentiation must be performed 
	/// within this method's scope.
	/// </summary>
	/// <param name="e">Event to be processed</param>
	virtual void OnEvent(Event& e) { }


	friend class EventBus;

};