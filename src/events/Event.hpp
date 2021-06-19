#pragma once
#include "../Keycodes.hpp"


using EventType_t = int;


enum class EventType : EventType_t {
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
	Event(EventType type): type(type), IntInt_i1(0), IntInt_i2(0) { }

	virtual ~Event() { }

	EventType GetType(void) const {
		return type;
	}

protected:
	// payload data
	// this is really the easiest (but not the best) way possible: no subclass members which can be sliced away.
	// & there is no need to allocate event instances on the heap (to avoid obj slicing in the queue) this way - event base types can be directly used.
	union {
		struct {
			float FloatFloat_f1;
			float FloatFloat_f2;
		};

		struct {
			float FloatInt_f;
			int FloatInt_i;
		};


		struct {
			int IntInt_i1;
			int IntInt_i2;
		};	

		struct {
			bool BoolInt_b;
			int BoolInt_i;
		};

		struct {
			unsigned int UintUint_ui1;
			unsigned int UintUint_ui2;
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
		IntInt_i1 = w;
		IntInt_i2 = h;
	}

	int GetScreenWidth(void) const { return this->IntInt_i1; }
	int GetScreenHeight(void) const { return this->IntInt_i2; }
	
};


class MouseButtonEvent final : public Event {
public:
	MouseButtonEvent(MouseButtonCode mbCode, bool isPressed) : Event(EventType::MouseButton) {		
		this->BoolInt_i = static_cast<int>(mbCode);
		this->BoolInt_b = isPressed;
	}	

	MouseButtonCode GetMbCode(void) { return static_cast<MouseButtonCode>(BoolInt_i); }
	bool GetIsPressed(void) { return BoolInt_b; }

};


class KeyEvent final : public Event {
public:
	KeyEvent(KeyCode keycode, bool isKeydown) : Event(EventType::Key) {
		BoolInt_i = static_cast<int>(keycode);
		BoolInt_b = isKeydown;		
	}

	KeyCode GetKeyCode(void) const { return static_cast<KeyCode>(BoolInt_i); }
	bool GetIsKeydown(void) const { return BoolInt_b; }

};


class MouseMoveEvent final : public Event {
public:
	MouseMoveEvent(int x, int y) : Event(EventType::MouseMove) {
		IntInt_i1 = x;
		IntInt_i2 = y;
	}

	int GetPositionX(void) const { return IntInt_i1; }
	int GetPositionY(void) const { return IntInt_i2; }
};


class MouseScrollEvent final : public Event {
public:
	MouseScrollEvent(MouseScrollDirection scrollDir, float delta):
		Event(EventType::MouseScroll) {

		FloatInt_i = static_cast<int>(scrollDir);
		FloatInt_f = delta;		
	}

	MouseScrollDirection GetScrollDirection(void) const { return static_cast<MouseScrollDirection>(FloatInt_i); }
	float GetDelta(void) const { return FloatInt_f; }
};