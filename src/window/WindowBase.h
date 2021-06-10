#pragma once
#include <string>
#include <functional>
#include "../events/EventEmitter.hpp"
#include "../events/EventBus.h"
#include <glm/glm.hpp>


class WindowBase : public EventEmitter {
protected:
	int width;
	int height;
	std::string title;	

public:
	WindowBase(EventBus* eventBus, int width, int height, const std::string& title);
	virtual ~WindowBase();
	
	virtual void SwapBuffers(void) = 0;
	virtual void DoFrame(void) = 0;
	virtual void MakeContextCurrent(void) = 0;
	virtual const glm::vec2 GetWindowRect() = 0;	

};