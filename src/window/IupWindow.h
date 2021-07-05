#pragma once
#include <string>
#include <iup/iup.h>
#include <iup/iupgl.h>
#include <iup/iup_class_cbs.hpp>
#include "WindowBase.h"
#include "../events/EventBus.h"
#include <glm/glm.hpp>


class IupWindow : public WindowBase {
protected:
	Ihandle* canvas;
	Ihandle* dlg;	

	// custom attribute, not needed in IupWindow base class
	Ihandle* labelGlVersion;	

public:
	IupWindow(EventBus* eventBus, int width, int height, const std::string& title);
	virtual ~IupWindow();

	virtual void Init(int argc, char** argv);
	void MakeContextCurrent(void) override;
	void SwapBuffers(void) override;
	void DoFrame(void) override;
	const glm::vec2 GetWindowRect(void) override;

	//custom method, not needed in IupWindow base class
	void SetGLVersionLabel(const std::string& glVersion);

protected:
	void InitCanvas(void);
	void InitDlg(Ihandle* topLevelIupBox = nullptr);

	// callbacks
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindow, CanvasResizeCb);
	IUP_CLASS_DECLARECALLBACK_IFn(IupWindow, DialogCloseCb);
	IUP_CLASS_DECLARECALLBACK_IFniiiis(IupWindow, CanvasButtonCb);
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindow, CanvasKeyCb);
	IUP_CLASS_DECLARECALLBACK_IFniis(IupWindow, CanvasMouseMoveCb);	
	IUP_CLASS_DECLARECALLBACK_IFnfiis(IupWindow, CanvasWheelCb);

};
