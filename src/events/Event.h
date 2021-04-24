#pragma once


enum class EventType {
	None = 0,
	WindowClose,
	WindowResize,
	KeyPress,
	KeyRelease,
	MouseClick,
	MouseScroll,
};



class Event {
protected:
	EventType type;

public:
	Event(EventType type);
	virtual ~Event();

};