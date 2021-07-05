#pragma once
#include <string>
#include <iup/iup.h>
#include <iup/iupgl.h>
#include <iup/iup_class_cbs.hpp>
#include "WindowBase.h"
#include "../events/EventBus.h"
#include <glm/glm.hpp>


/// <summary>
/// IUP window base class.
/// This class contains the entire logic which is needed to use an OpenGL canvas in a IUP window.
/// 
/// To add further UI elements, subclass this class and override Init(). (See this classes implementation of Init() as example).
/// </summary>
class IupWindowBase : public WindowBase {
protected:
	Ihandle* canvas;
	Ihandle* dlg;	
	
public:
	IupWindowBase(EventBus* eventBus, int width, int height, const std::string& title);
	virtual ~IupWindowBase();

	virtual void Init(int argc, char** argv);
	void MakeContextCurrent(void) override;
	void SwapBuffers(void) override;
	void DoFrame(void) override;
	const glm::vec2 GetWindowRect(void) override;

protected:
	void InitIup(int argc, char** argv);
	void InitCanvas(void);
	void InitDlg(Ihandle* topLevelIupBox = nullptr);
	void ShowDlg(void);

	// callbacks
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindowBase, CanvasResizeCb);
	IUP_CLASS_DECLARECALLBACK_IFn(IupWindowBase, DialogCloseCb);
	IUP_CLASS_DECLARECALLBACK_IFniiiis(IupWindowBase, CanvasButtonCb);
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindowBase, CanvasKeyCb);
	IUP_CLASS_DECLARECALLBACK_IFniis(IupWindowBase, CanvasMouseMoveCb);	
	IUP_CLASS_DECLARECALLBACK_IFnfiis(IupWindowBase, CanvasWheelCb);

};
