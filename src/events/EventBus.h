#pragma once
#include <map>
#include <vector>
#include <functional>
#include "Event.hpp"


class EventEmitter;
class EventListener;


/// <summary>
/// This class represents the Event bus. 
/// It shall be instanced only once throughout the entire application.
/// </summary>
class EventBus final {
private:
	std::vector<Event> eventQueue;	
	std::map<EventType, std::vector<EventListener*>, std::less<EventType>> listeners;

public:
	EventBus();
	~EventBus();
	
	/// <summary>
	/// Adds a listener (A listener is an EventListener subclass)
	/// </summary>
	/// <param name="type">The event type which shall be listened to</param>
	/// <param name="listener">The listener</param>
	void AddListener(EventType type, EventListener* listener);	

	/// <summary>
	/// Polls the event bus. 
	/// This method shall be called once per event processing interval (once per frame or once every n frames)
	/// </summary>
	void Poll(void);

private:
	void SendEvent(Event& e);

	friend class EventEmitter;
};