#pragma once
#include "IupWindowBase.h"


class IupUiWindow final: public IupWindowBase {
public:
	IupUiWindow(EventBus* eventBus, int width, int height, const std::string& title);

	~IupUiWindow();
};

