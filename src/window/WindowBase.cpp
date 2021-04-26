#include "WindowBase.h"


WindowBase::WindowBase(EventBus* eventBus, int width, int height, const std::string& title):
	EventEmitter(eventBus),
	width(width), height(height), title(title) { }


WindowBase::~WindowBase() { }



