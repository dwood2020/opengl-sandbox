#include "WindowBase.h"

WindowBase::WindowBase(int width, int height, const std::string& title):
	width(width), height(height), title(title), windowShouldClose(false) { }


WindowBase::~WindowBase() { }


bool WindowBase::GetWindowShouldClose(void) const {
	return this->windowShouldClose;
}
