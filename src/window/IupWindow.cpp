#include "IupWindow.h"
#include <string>
#include <iup/iupkey.h>


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
	IUP_CLASS_SETCALLBACK(canvas, "BUTTON_CB", CanvasButtonCb);
	IUP_CLASS_SETCALLBACK(canvas, "KEYPRESS_CB", CanvasKeyCb);
	IUP_CLASS_SETCALLBACK(canvas, "MOTION_CB", CanvasMouseMoveCb);

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


const glm::vec2 IupWindow::GetWindowRect(void) {

	int w, h;
	IupGetIntInt(canvas, "DRAWSIZE", &w, &h);

	glm::vec2 rect = {
		(float)w, (float)h
	};

	return rect;
}


// IUP callbacks
// -------------

int IupWindow::CanvasResizeCb(Ihandle* self, int width, int height) {

	WindowResizeEvent e(width, height);
	OnEvent(e);

	return IUP_DEFAULT;
}


int IupWindow::DialogCloseCb(Ihandle* self) {	

	WindowCloseEvent e;
	OnEvent(e);

	return IUP_DEFAULT;
}


int IupWindow::CanvasButtonCb(Ihandle* self, int button, int pressed, int x, int y, char* status) {

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
	OnEvent(e);

	return IUP_DEFAULT;
}


int IupWindow::CanvasKeyCb(Ihandle* self, int c, int press) {
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
	OnEvent(e);

	return IUP_DEFAULT;
}


int IupWindow::CanvasMouseMoveCb(Ihandle* self, int x, int y, char* status) {
	
	MouseMoveEvent e(x, y);
	OnEvent(e);

	return IUP_DEFAULT;
}


int IupWindow::CanvasWheelCb(Ihandle* self, float delta, int x, int y, char* status) {
	
	MouseScrollDirection dir = MouseScrollDirection::None;
	if (delta < -0.5f) {
		dir = MouseScrollDirection::Down;
	}
	else if (delta > 0.5f) {
		dir = MouseScrollDirection::Up;
	}

	MouseScrollEvent e(dir, 1.0f);
	OnEvent(e);

	return IUP_DEFAULT;
}



// custom function which will not be needed in IupWindowBase class
void IupWindow::SetGLVersionLabel(const std::string& glVersion) {
	IupSetAttribute(labelGlVersion, "TITLE", glVersion.c_str());
}