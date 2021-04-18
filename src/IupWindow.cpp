#include "IupWindow.h"


IupWindow::IupWindow(int width, int height, const std::string& title):
	WindowBase(width, height, title), canvas(nullptr), dlg(nullptr) {
	
	//IUP_CLASS_INITCALLBACK(dlg, IupWindow);
}


IupWindow::~IupWindow() { 
	IupClose();
}


void IupWindow::Init(int argc, char** argv) {
	IupOpen(&argc, &argv);
	IupGLCanvasOpen();

	Ihandle* label1 = IupLabel("This is a simple IUP Dialog. Running on OpenGL Version ");
	Ihandle* labelGlVersion = IupLabel(" xx");

	canvas = IupGLCanvas(NULL);
	IupSetAttribute(canvas, "BUFFER", "DOUBLE");	//NOTE: this makes the rendering MUCH faster
	IupSetAttribute(canvas, "DIRTY", "NO");
	
	IUP_CLASS_INITCALLBACK(canvas, IupWindow);
	IUP_CLASS_SETCALLBACK(canvas, "RESIZE_CB", CanvasResizeCb);

	Ihandle* dlg = IupDialog(IupVbox(IupHbox(label1, labelGlVersion, NULL), canvas, NULL));
	IupSetAttribute(dlg, "SIZE", "HALFxHALF");
	IupSetAttribute(dlg, "TITLE", "OpenGL Sandbox - Window");

	IUP_CLASS_INITCALLBACK(dlg, IupWindow);
	IUP_CLASS_SETCALLBACK(dlg, "CLOSE_CB", DialogCloseCb);

	IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
}


void IupWindow::MakeContextCurrent(void) {
	IupGLMakeCurrent(canvas);
}


void IupWindow::SwapBuffers(void) {
	IupGLSwapBuffers(canvas);
}


void IupWindow::DoFrame(void) {
	IupLoopStep();
}


void IupWindow::GetWindowRect(int& width, int& height) {
	IupGetIntInt(canvas, "DRAWSIZE", &width, &height);
}


// callbacks

int IupWindow::CanvasResizeCb(Ihandle* self, int width, int height) {
	if (onResize) {
		onResize(width, height);
	}
	return IUP_DEFAULT;
}

int IupWindow::DialogCloseCb(Ihandle* self) {
	this->windowShouldClose = true;
	if (onClose) {
		onClose();
	}
	return IUP_DEFAULT;
}