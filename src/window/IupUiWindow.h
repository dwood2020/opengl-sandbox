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

private:
	// callbacks
	IUP_CLASS_DECLARECALLBACK_IFnsii(IupUiWindow, ListProjectionModeActionCb);
	IUP_CLASS_DECLARECALLBACK_IFn(IupUiWindow, BtnResetViewActionCb);
	IUP_CLASS_DECLARECALLBACK_IFni(IupUiWindow, ToggleMouseSelectionActionCb);
};

