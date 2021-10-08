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
/// A basic understandig of IUP with C++ is needed to implement a subclass, see here: https://www.tecgraf.puc-rio.br/iup/
/// </summary>
class IupWindowBase : public WindowBase {
protected:
	Ihandle* canvas;
	Ihandle* dlg;	
	
public:
	IupWindowBase(EventBus* eventBus, int width, int height, const std::string& title);
	virtual ~IupWindowBase();

	/// <summary>
	/// Separate initialization method.
	/// This is only required for the IUP library.
	/// </summary>
	/// <param name="argc">Argc</param>
	/// <param name="argv">Argv</param>
	virtual void Init(int argc, char** argv);

	// overridden methods from WindowBase.
	void MakeContextCurrent(void) override;
	void SwapBuffers(void) override;
	void DoFrame(void) override;
	const glm::vec2 GetWindowRect(void) override;

protected:
	/// <summary>
	/// Initialize the IUP library.
	/// </summary>
	/// <param name="argc">Argc</param>
	/// <param name="argv">Argv</param>
	void InitIup(int argc, char** argv);

	/// <summary>
	/// Initializes the canvas component in the window. 
	/// Every IUP window in this context has a canvas.
	/// </summary>
	void InitCanvas(void);

	/// <summary>
	/// Initialize the actual IupDialog which makes out the entire window.
	/// </summary>
	/// <param name="topLevelIupBox">Top-level IUP Hbox or Vbox which holds all subcomponents.
	/// If this is null, the canvas becomes the top-level component.</param>
	void InitDlg(Ihandle* topLevelIupBox = nullptr);

	/// <summary>
	/// Show the Window (the IUP dialog) on screen.
	/// </summary>
	void ShowDlg(void);

	// callbacks
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindowBase, CanvasResizeCb);
	IUP_CLASS_DECLARECALLBACK_IFn(IupWindowBase, DialogCloseCb);
	IUP_CLASS_DECLARECALLBACK_IFniiiis(IupWindowBase, CanvasButtonCb);
	IUP_CLASS_DECLARECALLBACK_IFnii(IupWindowBase, CanvasKeyCb);
	IUP_CLASS_DECLARECALLBACK_IFniis(IupWindowBase, CanvasMouseMoveCb);	
	IUP_CLASS_DECLARECALLBACK_IFnfiis(IupWindowBase, CanvasWheelCb);

};
