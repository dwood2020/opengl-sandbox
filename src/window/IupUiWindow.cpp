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

	IUP_CLASS_INITCALLBACK(listProjectionMode, IupUiWindow);
	IUP_CLASS_SETCALLBACK(listProjectionMode, "ACTION", ListProjectionModeActionCb);

	// Reset view button
	Ihandle* btnResetView = IupButton("Reset View", NULL);
	IUP_CLASS_INITCALLBACK(btnResetView, IupUiWindow);
	IUP_CLASS_SETCALLBACK(btnResetView, "ACTION", BtnResetViewActionCb);

	// Top bar	
	Ihandle* hboxTop = IupHbox(hboxOpenGlVersion, IupFill(), btnResetView, hboxProjectionMode, NULL);	
	IupSetAttribute(hboxTop, "GAP", "10");
	IupSetAttribute(hboxTop, "ALIGNMENT", "ACENTER");	
	IupSetAttribute(hboxTop, "EXPAND", "YES");


	InitDlg(IupVbox(hboxTop, canvas, NULL));
	ShowDlg();	
}


void IupUiWindow::SetGLVersionLabel(const std::string& glVersion) {
	IupSetAttribute(labelGlVersion, "TITLE", glVersion.c_str());
}


// IUP callbacks
// -------------

int IupUiWindow::ListProjectionModeActionCb(Ihandle* ih, char* text, int item, int state) {
	
	if (state == 1) {
		ProjectionMode mode = static_cast<ProjectionMode>(item);
		ProjectionModeChangedEvent e(mode);
		OnEvent(e);
	}	
	
	//Debug:
	/*std::string s = "ProjectionModeActionCb: Item:" + std::to_string(item) + "  State: " + std::to_string(state);
	IupMessage("Debug", s.c_str());*/

	return IUP_DEFAULT;
}


int IupUiWindow::BtnResetViewActionCb(Ihandle* ih) {
	ResetViewEvent e;
	OnEvent(e);
	return IUP_DEFAULT;
}