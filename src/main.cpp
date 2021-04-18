#include <iostream>
#include <iup/iup.h>
#include "glad/glad.h"
#include <iup/iupgl.h>


bool windowShouldClose = false;
bool glReady = false;

void CanvasDrawFrame(Ihandle* canvas) {
	glClear(GL_COLOR_BUFFER_BIT);
	IupGLSwapBuffers(canvas);
}


// I do not really need this callback, as I decide manually when to redraw the canvas anyway.
int CanvasActionCb(Ihandle* canvas) {

	if (!glReady) {
		return IUP_DEFAULT;
	}

	/*int width, height;
	IupGetIntInt(canvas, "DRAWSIZE", &width, &height);
	glViewport(0, 0, width, height);*/

	//glClearColor(0.075f, 0.196f, 0.325f, 1.0f);

	CanvasDrawFrame(canvas);
	std::cout << "CanvasActionCb CALLED!" << std::endl;

	
	return IUP_DEFAULT;
}


int CanvasResizeCb(Ihandle* canvas, int width, int height) {
	if (!glReady) {
		return IUP_DEFAULT;
	}

	std::cout << "CanvasResizeCb CALLED!" << std::endl;

	/*int width, height;
	IupGetIntInt(canvas, "DRAWSIZE", &width, &height);*/

	glViewport(0, 0, width, height);

	return IUP_DEFAULT;
}


int DialogCloseCb(Ihandle* self) {
	windowShouldClose = true;
	return IUP_DEFAULT;
}


int main(int argc, char** argv) {

	IupOpen(&argc, &argv);
	IupGLCanvasOpen();

	Ihandle* label1 = IupLabel("This is a simple IUP Dialog. Running on OpenGL Version ");
	Ihandle* labelGlVersion = IupLabel(" xx");
	Ihandle* canvas;

	canvas = IupGLCanvas(NULL);
	IupSetAttribute(canvas, "BUFFER", "DOUBLE");	//NOTE: this makes the rendering MUCH faster
	IupSetAttribute(canvas, "DIRTY", "NO");
	IupSetCallback(canvas, "ACTION", (Icallback)CanvasActionCb);
	IupSetCallback(canvas, "RESIZE_CB", (Icallback)CanvasResizeCb);


	Ihandle* dlg = IupDialog(IupVbox(IupHbox(label1, labelGlVersion, NULL), canvas, NULL));
	IupSetAttribute(dlg, "SIZE", "HALFxHALF");
	IupSetAttribute(dlg, "TITLE", "OpenGL Sandbox - Window");
	IupSetCallback(dlg, "CLOSE_CB", (Icallback)DialogCloseCb);

	IupShowXY(dlg, IUP_CENTER, IUP_CENTER);

	//NOTE: gladLoadGL only workes with active OpenGL context.
	// AND The context can only be "active" after the window becomes visible.
	IupGLMakeCurrent(canvas);

	if (!gladLoadGL()) {
		IupMessageError(NULL, "gladLoadGL failed");
		std::cout << "gladLoadGL failed" << std::endl;
		return IUP_ERROR;
	}
	glReady = true;

	int width, height;
	IupGetIntInt(canvas, "DRAWSIZE", &width, &height);
	glViewport(0, 0, width, height);

	glClearColor(0.075f, 0.196f, 0.325f, 1.0f);

	auto glVersionStr = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << (const char*)glVersionStr << std::endl;

	IupSetAttribute(labelGlVersion, "TITLE", (const char*)glVersionStr);
	//Do one refresh call to avoid artifacts of missing label string parts
	IupLoopStep();

	const int n = 3;
	int k = 0;

	while (!windowShouldClose) {

		// this makes the canvas get drawn every n-th frame
		k += 1;
		if (k > n) {
			k = 0;
			//CanvasActionCb(canvas);
			CanvasDrawFrame(canvas);
		}

		IupLoopStep();
	}
	//IupExitLoop();

	//IupMainLoop();

	IupClose();
	return 0;
}