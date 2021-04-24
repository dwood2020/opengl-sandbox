#pragma once


namespace eventtype {
	enum EventType : unsigned int {
		NONE = 0x0,
		WINDOW_CLOSE = (1 << 0),	// = 0b...0001 = 1u
		WINDOW_RESIZE = (1 << 1),	// = 0b...0010 = 2u
		// RESERVED (1 << 2)
		// RESERVED (1 << 3)
		KEY_PRESS = (1 << 4),		// = 0b...1'0000 = 16u
		KEY_RELEASE = (1 << 5),
		MOUSE_CLICK = (1 << 6),
		MOUSE_SCROLL = (1 << 7),
		ALL = 0b1111'1111			//TODO: Make this nicer, try to avoid binary notation
	};
}


using eventtype::EventType;


class Event {
protected:
	EventType type;

	Event(EventType type);

public:
	Event();
	virtual ~Event();

	EventType GetType(void) const;

};



class WindowCloseEvent : public Event {
public:
	// no additional parameters

public:
	WindowCloseEvent() : Event(EventType::WINDOW_CLOSE) { }

};

