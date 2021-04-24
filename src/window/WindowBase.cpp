#include "WindowBase.h"


WindowBase::WindowBase(EventBus* eventBus, int width, int height, const std::string& title):
	EventEmitter(eventBus),
	width(width), height(height), title(title), windowShouldClose(false) { }


WindowBase::~WindowBase() { }


bool WindowBase::GetWindowShouldClose(void) const {
	return this->windowShouldClose;
}


void WindowBase::SetOnResize(std::function<void(int, int)> f) {
	onResize = f;
}


void WindowBase::SetOnClose(std::function<void(void)> f) {
	onClose = f;
}
