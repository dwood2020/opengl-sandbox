#include "IupUiWindow.h"


IupUiWindow::IupUiWindow(EventBus* eventBus, int width, int height, const std::string& title):
	IupWindowBase(eventBus, width, height, title), labelGlVersion(nullptr) { }


IupUiWindow::~IupUiWindow() { }


void IupUiWindow::Init(int argc, char** argv) {

	InitIup(argc, argv);

	InitCanvas();

	Ihandle* label1 = IupLabel("This is a simple IUP Dialog. Running on OpenGL Version ");
	labelGlVersion = IupLabel(" xx");

	InitDlg(IupVbox(IupHbox(label1, labelGlVersion, NULL), canvas, NULL));	

	ShowDlg();	
}


void IupUiWindow::SetGLVersionLabel(const std::string& glVersion) {
	IupSetAttribute(labelGlVersion, "TITLE", glVersion.c_str());
}