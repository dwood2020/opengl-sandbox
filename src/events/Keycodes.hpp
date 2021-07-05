#pragma once


enum class MouseButtonCode {
	None = 0,
	Left = 1,
	Middle,
	Right
};


enum class KeyCode {
	None = 0,
	A = 1,
	D = 4,
	S = 19,
	W = 23,
	Esc,
	Space
};


enum class MouseScrollDirection {
	None = 0,
	Up,
	Down
};


//TODO: Relocate this!
enum class ProjectionMode {
	Perspective = 1,
	Orthographic = 2
};