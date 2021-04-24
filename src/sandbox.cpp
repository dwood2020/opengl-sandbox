#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include "events/EventBus.h"
#include "window/IupWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"

#include <ctime>
#include <cmath>


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
	
	std::string glVersionStr = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersionStr << std::endl;
	window.SetGLVersionLabel(glVersionStr);


	// test of new mesh class
	std::vector<glm::vec3> vertices = {
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f}
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 1
	};

	Mesh mesh(vertices, indices);
	mesh.Prepare();
	mesh.SetMode(GL_TRIANGLES);	

	Shader vertexShader(Shader::ReadSourceFromFile("res/vertex.glsl").c_str(), GL_VERTEX_SHADER);
	Shader fragmentShader(Shader::ReadSourceFromFile("res/fragment.glsl").c_str(), GL_FRAGMENT_SHADER);
	vertexShader.CheckCompilationStatus();
	fragmentShader.CheckCompilationStatus();

	ShaderProgram shaderProgram(vertexShader, fragmentShader);
	shaderProgram.CheckLinkStatus();

	shaderProgram.Use();	

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	while (!window.GetWindowShouldClose()) {
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Uniform test
		float alpha = abs(sin(std::time(0)));		
		shaderProgram.SetUniformFloat("uniformAlpha", alpha);

		shaderProgram.Use();
		mesh.Draw();		

		window.SwapBuffers();
		window.DoFrame();		
	}

	return 0;
}
