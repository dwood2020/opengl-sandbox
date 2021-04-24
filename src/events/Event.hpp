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
	Event(EventType type): type(type), x(0), y(0) { }
	virtual ~Event() { }

	const EventType& GetType(void) const {
		return type;
	}

	// payload data
	// this is really the easiest (but not the best) way possible: no subclass members which can be sliced away.
	// & there is no need to allocate event instances on the heap (to avoid obj slicing in the queue) this way - event base types can be directly used.
	union {
		struct {
			float x;
			float y;
		};

		struct {
			int w;
			int h;
		};
	};

};


// subclassed events

class WindowCloseEvent : public Event {
public:
	WindowCloseEvent(): Event(EventType::WindowClose) { }
	virtual ~WindowCloseEvent() { }
};


class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(int w, int h): Event(EventType::WindowResize) {
		this->w = w;
		this->h = h;
	}

	virtual ~WindowResizeEvent() { }
};