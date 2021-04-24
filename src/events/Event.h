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

	union {
		struct {
			float x_float;
			float y_float;
		};

		struct {
			int w;
			int h;
		};
	};

};


// subclassed events
//TODO: think about where to put these

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