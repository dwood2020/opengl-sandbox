#pragma once
#include <string>
#include "WindowBase.h"
#include <iup/iup.h>
#include <iup/iupgl.h>
#include <iup/iup_class_cbs.hpp>


class IupWindow : public WindowBase {
protected:
	Ihandle* canvas;
	Ihandle* dlg;	

	// custom attribute, not needed in IupWindow base class
	Ihandle* labelGlVersion;	

public:
	IupWindow(int width, int height, const std::string& title);
	virtual ~IupWindow();

	virtual void Init(int argc, char** argv);
	void MakeContextCurrent(void) override;
	void SwapBuffers(void) override;
	void DoFrame(void) override;
	void GetWindowRect(int& width, int& height) override;

	//custom method, not needed in IupWindow base class
	void SetGLVersionLabel(const std::string& glVersion);

protected:
	// callbacks
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindow, CanvasResizeCb);
	IUP_CLASS_DECLARECALLBACK_IFn(IupWindow, DialogCloseCb);


};
