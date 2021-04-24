#pragma once


enum class EventType {
	None = 0,
	WindowClose,
	WindowResize,
	KeyPress,
	KeyRelease,
	MouseMove,
	MouseClick,
	MouseScroll,
};



class Event {
protected:
	EventType type;

public:
	Event(EventType type);
	virtual ~Event();

	const EventType& GetType(void) const;

};