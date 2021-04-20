#pragma once
#include <cctype>


namespace eventtype {
	enum EventT {
		NONE = 0x0,
		WINDOW_CLOSE = (1 << 0),	// = 1 << 0 = 0b0...0001
		WINDOW_RESIZE = (1 << 1),
		// RESERVED (1 << 2)
		// RESERVED (1 << 3)
		KEY_PRESS = (1 << 4),
		KEY_RELEASE = (1 << 5),
		MOUSE_CLICK = (1 << 6),
		MOUSE_SCROLL = (1 << 7)
	};

}


class Event {

};



