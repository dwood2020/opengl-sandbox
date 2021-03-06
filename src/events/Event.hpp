#pragma once
#include "Keycodes.hpp"


/// <summary>
/// The data type for the EventType-enumeration.
/// </summary>
using EventType_t = int;


/// <summary>
/// All event types are defined here.
/// </summary>
enum class EventType : EventType_t {
	None = 0,
	WindowClose,
	WindowResize,
	Key,	
	MouseMove,
	MouseButton,
	MouseScroll,

	ProjectionModeChanged,	//TODO: Relocate this event type def!
	ResetView,
	ToggleSelectMode,
};


/// <summary>
/// This class represents a generic event.
/// It holds a type enum and a union of event parameters.
/// The parameters are accessed via getters/setters defined in event subclasses.
/// Instanciation of an event subclass also sets the EventType enum.
/// (This makes easy processing possible by preventing object slicing)
/// </summary>
class Event {
protected:
	EventType type;

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="type">Event type</param>
	Event(EventType type): type(type) {
		IntInt.i1 = 0;
		IntInt.i2 = 0;
	}


	virtual ~Event() { }


	/// <summary>
	/// Gets the Event type.
	/// </summary>
	/// <returns>Event type</returns>
	EventType GetType(void) const {
		return type;
	}

protected:
	// payload data
	// this is really the easiest (but not the best) way possible: no subclass members which could be sliced away.
	// & there is no need to allocate event instances on the heap (to avoid obj slicing in the queue) this way - event base types can be directly used.
	union {
		struct {
			float f1;
			float f2;
		} FloatFloat;

		struct {
			float f;
			int i;
		} FloatInt;


		struct {
			int i1;
			int i2;
		} IntInt;	

		struct {
			bool b;
			int i;
		} BoolInt;

		struct {
			unsigned int ui1;
			unsigned int ui2;
		} UintUint;		
	};

};


// subclassed events
// -----------------

class WindowCloseEvent : public Event {
public:
	WindowCloseEvent(): Event(EventType::WindowClose) { }
	virtual ~WindowCloseEvent() { }
};


class WindowResizeEvent final : public Event {
public:
	WindowResizeEvent(int w, int h): Event(EventType::WindowResize) {			
		IntInt.i1 = w;
		IntInt.i2 = h;
	}

	int GetScreenWidth(void) const { return this->IntInt.i1; }
	int GetScreenHeight(void) const { return this->IntInt.i2; }
	
};


class MouseButtonEvent final : public Event {
public:
	MouseButtonEvent(MouseButtonCode mbCode, bool isPressed) : Event(EventType::MouseButton) {		
		this->BoolInt.i = static_cast<int>(mbCode);
		this->BoolInt.b = isPressed;
	}	

	MouseButtonCode GetMbCode(void) { return static_cast<MouseButtonCode>(BoolInt.i); }
	bool GetIsPressed(void) { return BoolInt.b; }

};


class KeyEvent final : public Event {
public:
	KeyEvent(KeyCode keycode, bool isKeydown) : Event(EventType::Key) {
		BoolInt.i = static_cast<int>(keycode);
		BoolInt.b = isKeydown;		
	}

	KeyCode GetKeyCode(void) const { return static_cast<KeyCode>(BoolInt.i); }
	bool GetIsKeydown(void) const { return BoolInt.b; }

};


class MouseMoveEvent final : public Event {
public:
	MouseMoveEvent(int x, int y) : Event(EventType::MouseMove) {
		IntInt.i1 = x;
		IntInt.i2 = y;
	}

	int GetPositionX(void) const { return IntInt.i1; }
	int GetPositionY(void) const { return IntInt.i2; }
};


class MouseScrollEvent final : public Event {
public:
	MouseScrollEvent(MouseScrollDirection scrollDir, float delta):
		Event(EventType::MouseScroll) {

		FloatInt.i = static_cast<int>(scrollDir);
		FloatInt.f = delta;		
	}

	MouseScrollDirection GetScrollDirection(void) const { return static_cast<MouseScrollDirection>(FloatInt.i); }
	float GetDelta(void) const { return FloatInt.f; }
};


//TODO: Relocate this event
class ProjectionModeChangedEvent final : public Event {
public:
	ProjectionModeChangedEvent(ProjectionMode projectionMode) :
		Event(EventType::ProjectionModeChanged) {

		BoolInt.i = static_cast<int>(projectionMode);
		BoolInt.b = false;
	}

	ProjectionMode GetProjectionMode(void) {
		return static_cast<ProjectionMode>(BoolInt.i);
	}
};


class ResetViewEvent final : public Event {
public:
	ResetViewEvent() : Event(EventType::ResetView) { }
};


class ToggleSelectModeEvent final : public Event {
public:
	ToggleSelectModeEvent(bool stateActive) : Event(EventType::ToggleSelectMode) {
		BoolInt.b = stateActive;
	}

	bool GetSelectMode(void) const {
		return BoolInt.b;
	}
};