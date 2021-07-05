#include "IupUiWindow.h"


IupUiWindow::IupUiWindow(EventBus* eventBus, int width, int height, const std::string& title):
	IupWindowBase(eventBus, width, height, title) { }


IupUiWindow::~IupUiWindow() { }
