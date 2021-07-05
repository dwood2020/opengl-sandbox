#pragma once
#include "IupWindowBase.h"


class IupUiWindow final: public IupWindowBase {
private:
	Ihandle* labelGlVersion;

public:
	IupUiWindow(EventBus* eventBus, int width, int height, const std::string& title);	

	~IupUiWindow();

	void Init(int argc, char** argv) override;

	void SetGLVersionLabel(const std::string& glVersion);
};
