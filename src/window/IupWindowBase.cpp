#include "IupWindowBase.h"
#include <string>
#include <iup/iupkey.h>


IupWindowBase::IupWindowBase(EventBus* eventBus, int width, int height, const std::string& title):
	WindowBase(eventBus, width, height, title), canvas(nullptr), dlg(nullptr) { }


IupWindowBase::~IupWindowBase() { 
	IupClose();
}


void IupWindowBase::Init(int argc, char** argv) {
	InitIup(argc, argv);
	
	InitCanvas();

	InitDlg();

	ShowDlg();
}


void IupWindowBase::MakeContextCurrent(void) {
	IupGLMakeCurrent(canvas);
}


void IupWindowBase::SwapBuffers(void) {
	IupGLSwapBuffers(canvas);
}


void IupWindowBase::DoFrame(void) {
	IupLoopStep();
}


void IupWindowBase::InitIup(int argc, char** argv) {
	IupOpen(&argc, &argv);
	IupGLCanvasOpen();
}


void IupWindowBase::InitCanvas(void) {
	
	canvas = IupGLCanvas(NULL);
	IupSetAttribute(canvas, "BUFFER", "DOUBLE");	//NOTE: this makes the rendering MUCH faster
	IupSetAttribute(canvas, "DIRTY", "NO");

	IUP_CLASS_INITCALLBACK(canvas, IupWindowBase);
	IUP_CLASS_SETCALLBACK(canvas, "RESIZE_CB", CanvasResizeCb);
	IUP_CLASS_SETCALLBACK(canvas, "BUTTON_CB", CanvasButtonCb);
	IUP_CLASS_SETCALLBACK(canvas, "KEYPRESS_CB", CanvasKeyCb);
	IUP_CLASS_SETCALLBACK(canvas, "MOTION_CB", CanvasMouseMoveCb);
	IUP_CLASS_SETCALLBACK(canvas, "WHEEL_CB", CanvasWheelCb);
}


void IupWindowBase::InitDlg(Ihandle* topLevelIupBox) {

	if (topLevelIupBox == nullptr) {
		Ihandle* defaultBox = IupVbox(canvas, NULL);
		dlg = IupDialog(defaultBox);
	}
	else {
		dlg = IupDialog(topLevelIupBox);
	}

	
	std::string size = std::to_string(this->width) + 'X' + std::to_string(this->height);
	IupSetAttribute(dlg, "RASTERSIZE", size.c_str());
	IupSetAttribute(dlg, "TITLE", this->title.c_str());

	IUP_CLASS_INITCALLBACK(dlg, IupWindowBase);
	IUP_CLASS_SETCALLBACK(dlg, "CLOSE_CB", DialogCloseCb);
}


void IupWindowBase::ShowDlg(void) {
	IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
}


const glm::vec2 IupWindowBase::GetWindowRect(void) {

	int w, h;
	IupGetIntInt(canvas, "DRAWSIZE", &w, &h);

	glm::vec2 rect = {
		(float)w, (float)h
	};

	return rect;
}


// IUP callbacks
// -------------

int IupWindowBase::CanvasResizeCb(Ihandle* self, int width, int height) {

	WindowResizeEvent e(width, height);
	EmitEvent(e);

	return IUP_DEFAULT;
}


int IupWindowBase::DialogCloseCb(Ihandle* self) {	

	WindowCloseEvent e;
	EmitEvent(e);

	return IUP_DEFAULT;
}


int IupWindowBase::CanvasButtonCb(Ihandle* self, int button, int pressed, int x, int y, char* status) {

	//TODO: Move this into a central lookup table/function (maybe namespace in keycodes?)
	MouseButtonCode mbCode;
	switch (button) {
	case IUP_BUTTON1:
		mbCode = MouseButtonCode::Left; break;
	case IUP_BUTTON2:
		mbCode = MouseButtonCode::Middle; break;
	case IUP_BUTTON3:
		mbCode = MouseButtonCode::Right; break;
	default:
		mbCode = MouseButtonCode::None;
	}

	MouseButtonEvent e(mbCode, (bool)pressed);
	EmitEvent(e);

	return IUP_DEFAULT;
}


int IupWindowBase::CanvasKeyCb(Ihandle* self, int c, int press) {
	KeyCode keycode;
	
	switch (c) {
	case K_A:
	case K_a:
		keycode = KeyCode::A; break;
	case K_D:
	case K_d:
		keycode = KeyCode::D; break;
	case K_S:
	case K_s:
		keycode = KeyCode::S; break;
	case K_W:
	case K_w:
		keycode = KeyCode::W; break;
	case K_ESC:
		keycode = KeyCode::Esc; break;
	case K_SP:
		keycode = KeyCode::Space; break;
	default:
		keycode = KeyCode::None; break;
	}

	KeyEvent e(keycode, (bool)press);
	EmitEvent(e);

	return IUP_DEFAULT;
}


int IupWindowBase::CanvasMouseMoveCb(Ihandle* self, int x, int y, char* status) {
	
	MouseMoveEvent e(x, y);
	EmitEvent(e);

	return IUP_DEFAULT;
}


int IupWindowBase::CanvasWheelCb(Ihandle* self, float delta, int x, int y, char* status) {
	
	MouseScrollDirection dir = MouseScrollDirection::None;
	if (delta < -0.5f) {
		dir = MouseScrollDirection::Down;
	}
	else if (delta > 0.5f) {
		dir = MouseScrollDirection::Up;
	}

	MouseScrollEvent e(dir, 1.0f);
	EmitEvent(e);

	return IUP_DEFAULT;
}


