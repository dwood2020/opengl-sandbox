#include "IupUiWindow.h"


IupUiWindow::IupUiWindow(EventBus* eventBus, int width, int height, const std::string& title):
	IupWindowBase(eventBus, width, height, title), labelGlVersion(nullptr) { }


IupUiWindow::~IupUiWindow() { }


void IupUiWindow::Init(int argc, char** argv) {

	InitIup(argc, argv);
	InitCanvas();

	// OpenGL Version 
	Ihandle* labelGlVersionExplanation = IupLabel("OpenGL Version: ");
	labelGlVersion = IupLabel("xxxxxxxxxxxxxxxxx");
	IupSetAttribute(labelGlVersion, "EXPAND", "TRUE");
	Ihandle* hboxOpenGlVersion = IupHbox(labelGlVersionExplanation, labelGlVersion, NULL);
	IupSetAttribute(hboxOpenGlVersion, "GAP", "2");	

	// Projection mode	
	Ihandle* listProjectionMode = IupList(NULL);
	IupSetAttribute(listProjectionMode, "DROPDOWN", "YES");
	IupSetAttribute(listProjectionMode, "1", "Perspective");
	IupSetAttribute(listProjectionMode, "2", "Orthographic");
	IupSetAttribute(listProjectionMode, "VALUE", "1");
	Ihandle* labelProjectionMode = IupLabel("Projection mode:");
	Ihandle* hboxProjectionMode = IupHbox(labelProjectionMode, listProjectionMode, NULL);
	IupSetAttribute(hboxProjectionMode, "ALIGNMENT", "ACENTER");
	IupSetAttribute(hboxProjectionMode, "GAP", "2");

	// Top bar	
	Ihandle* hboxTop = IupHbox(hboxOpenGlVersion, IupFill(), hboxProjectionMode, NULL);	
	//IupSetAttribute(hboxTop, "GAP", "50");
	IupSetAttribute(hboxTop, "ALIGNMENT", "ACENTER");	
	IupSetAttribute(hboxTop, "EXPAND", "YES");


	InitDlg(IupVbox(hboxTop, canvas, NULL));
	ShowDlg();	
}


void IupUiWindow::SetGLVersionLabel(const std::string& glVersion) {
	IupSetAttribute(labelGlVersion, "TITLE", glVersion.c_str());
}