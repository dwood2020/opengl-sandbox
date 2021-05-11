#pragma once
#include "../Keycodes.hpp"


enum class EventType {
	None = 0,
	WindowClose,
	WindowResize,
	Key,	
	MouseMove,
	MouseButton,
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

protected:
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

		struct {
			MouseButtonCode mbCode;
			bool isPressed;
		};

		struct {
			KeyCode keyCode;
			bool isKeydown;
		};

		struct {
			int xScreen;
			int yScreen;	//TODO: Think about this. Its a double definition of two ints
		};

		struct {
			MouseScrollDirection scrollDir;
			float delta;
		};
	};

};


// subclassed events

class WindowCloseEvent : public Event {
public:
	WindowCloseEvent(): Event(EventType::WindowClose) { }
	virtual ~WindowCloseEvent() { }
};


class WindowResizeEvent final : public Event {
public:
	WindowResizeEvent(int w, int h): Event(EventType::WindowResize) {
		this->w = w;
		this->h = h;
	}

	int GetScreenWidth(void) const { return this->w; }
	int GetScreenHeight(void) const { return this->h; }
	
};


class MouseButtonEvent final : public Event {
public:
	MouseButtonEvent(MouseButtonCode mbCode, bool isPressed) : Event(EventType::MouseButton) {
		this->mbCode = mbCode;
		this->isPressed = isPressed;
	}	

	const MouseButtonCode& GetMbCode(void) { return this->mbCode; }
	bool GetIsPressed(void) { return this->isPressed; }

};


class KeyEvent final : public Event {
public:
	KeyEvent(KeyCode keycode, bool isKeydown) : Event(EventType::Key) {
		this->keyCode = keycode;
		this->isKeydown = isKeydown;
	}

	const KeyCode& GetKeyCode(void) const { return this->keyCode; }
	bool GetIsKeydown(void) const { return this->isKeydown; }

};


class MouseMoveEvent final : public Event {
public:
	MouseMoveEvent(int x, int y) : Event(EventType::MouseMove) {
		this->xScreen = x;
		this->yScreen = y;
	}

	int GetPositionX(void) const { return this->xScreen; }
	int GetPositionY(void) const { return this->yScreen; }
};


class MouseScrollEvent final : public Event {
public:
	MouseScrollEvent(MouseScrollDirection scrollDir, float delta):
		Event(EventType::MouseScroll) {

		this->scrollDir = scrollDir;
		this->delta = delta;
	}

	const MouseScrollDirection& GetScrollDirection(void) const { return this->scrollDir; }
	float GetDelta(void) const { return this->delta; }
};