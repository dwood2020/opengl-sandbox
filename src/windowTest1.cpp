#include <iostream>
#include "glad/glad.h"
//#include <iup/iup.h>
//#include <iup/iupgl.h>
#include "IupWindow.h"



void OnWindowResize(int w, int h) {
	glViewport(0, 0, w, h);
}



int main(int argc, char* argv[]) {

	IupWindow window(800, 600, "IupWindow class - Test 1");		
	window.Init(argc, argv);

	window.MakeContextCurrent();

	//now load OpenGL
	if (!gladLoadGL()) {		
		std::cout << "gladLoadGL failed" << std::endl;
		return -1;
	}

	int w, h;
	window.GetWindowRect(w, h);
	glViewport(0, 0, w, h);

	window.SetOnResize(OnWindowResize);

	glClearColor(0.075f, 0.196f, 0.325f, 1.0f);

	auto glVersionStr = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << (const char*)glVersionStr << std::endl;

	while (!window.GetWindowShouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		window.SwapBuffers();
		window.DoFrame();
	}

	return 0;
}
