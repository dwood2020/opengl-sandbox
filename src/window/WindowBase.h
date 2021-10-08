#pragma once
#include <string>
#include <functional>
#include "../events/EventEmitter.hpp"
#include "../events/EventBus.h"
#include <glm/glm.hpp>


/// <summary>
/// This class represents a base for all window abstraction classes.
/// It defines the required interface.
/// The intention is to provide the possibility to implement different window classes which
/// use different libraries (e.g. IUP and GLFW).
/// </summary>
class WindowBase : public EventEmitter {
protected:
	int width;
	int height;
	std::string title;	

public:
	/// <summary>
	/// Constructor.
	/// </summary>
	/// <param name="eventBus">Event bus</param>
	/// <param name="width">Window witdh</param>
	/// <param name="height">Window height</param>
	/// <param name="title">Window title</param>
	WindowBase(EventBus* eventBus, int width, int height, const std::string& title);
	
	virtual ~WindowBase();
	

	/// <summary>
	/// Swaps the window buffers.
	/// </summary>
	virtual void SwapBuffers(void) = 0;


	/// <summary>
	/// Does the next frame step.
	/// </summary>
	virtual void DoFrame(void) = 0;


	/// <summary>
	/// Makes the provided OpenGL context current.
	/// </summary>
	virtual void MakeContextCurrent(void) = 0;


	/// <summary>
	/// Gets the window x- and y-dimensions (the "rectangle")
	/// </summary>
	/// <returns>Window dimensions</returns>
	virtual const glm::vec2 GetWindowRect() = 0;	

};