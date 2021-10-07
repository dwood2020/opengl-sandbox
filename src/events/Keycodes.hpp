#pragma once


/// <summary>
/// Definition of mouse button codes.
/// </summary>
enum class MouseButtonCode {
	None = 0,
	Left = 1,
	Middle,
	Right
};


/// <summary>
/// Definition of keyboard button codes.
/// </summary>
enum class KeyCode {
	None = 0,
	A = 1,
	D = 4,
	S = 19,
	W = 23,
	Esc,
	Space
};


/// <summary>
/// Definition of mouse scroll directions
/// </summary>
enum class MouseScrollDirection {
	None = 0,
	Up,
	Down
};


//TODO: Relocate this!
/// <summary>
/// Definition of camera projection modes
/// </summary>
enum class ProjectionMode {
	Perspective = 1,
	Orthographic = 2
};