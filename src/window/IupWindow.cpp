#include "IupWindow.h"
#include <string>


IupWindow::IupWindow(EventBus* eventBus, int width, int height, const std::string& title):
	WindowBase(eventBus, width, height, title), labelGlVersion(nullptr), canvas(nullptr), dlg(nullptr) { }


IupWindow::~IupWindow() { 
	IupClose();
}


void IupWindow::Init(int argc, char** argv) {
	IupOpen(&argc, &argv);
	IupGLCanvasOpen();

	Ihandle* label1 = IupLabel("This is a simple IUP Dialog. Running on OpenGL Version ");
	labelGlVersion = IupLabel(" xx");

	canvas = IupGLCanvas(NULL);
	IupSetAttribute(canvas, "BUFFER", "DOUBLE");	//NOTE: this makes the rendering MUCH faster
	IupSetAttribute(canvas, "DIRTY", "NO");
	
	IUP_CLASS_INITCALLBACK(canvas, IupWindow);
	IUP_CLASS_SETCALLBACK(canvas, "RESIZE_CB", CanvasResizeCb);

	Ihandle* dlg = IupDialog(IupVbox(IupHbox(label1, labelGlVersion, NULL), canvas, NULL));
	std::string size = std::to_string(this->width) + 'X' + std::to_string(this->height);
	IupSetAttribute(dlg, "RASTERSIZE", size.c_str());
	IupSetAttribute(dlg, "TITLE", this->title.c_str());

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


// IUP callbacks
// -------------

int IupWindow::CanvasResizeCb(Ihandle* self, int width, int height) {
	/*if (onResize) {
		onResize(width, height);
	}*/

	WindowResizeEvent e(width, height);
	OnEvent(e);

	return IUP_DEFAULT;
}


int IupWindow::DialogCloseCb(Ihandle* self) {
	this->windowShouldClose = true;
	/*if (onClose) {
		onClose();
	}*/

	WindowCloseEvent e;
	OnEvent(e);

	return IUP_DEFAULT;
}



// custom function which will not be needed in IupWindowBase class
void IupWindow::SetGLVersionLabel(const std::string& glVersion) {
	IupSetAttribute(labelGlVersion, "TITLE", glVersion.c_str());
}