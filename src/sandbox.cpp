#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "events/EventBus.h"
#include "window/IupWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"



bool g_exitProgram = false;


void OnWindowResize(Event& e) {
	std::cout << "OnWindowResize called!" << std::endl;
	glViewport(0, 0, e.w, e.h);
}


// this is now a proof of concept
void OnWindowClose(Event& e) {
	std::cout << "Window Close event received!" << std::endl;
	g_exitProgram = true;
}


void OnMouseButtonClick(Event& e) {
	std::cout << "Mouse button " << ((e.press) ? "clicked" : "released") << ": " << (int)e.mbCode << std::endl;	
}


int main(int argc, char* argv[]) {

	EventBus eventBus;


	IupWindow window(&eventBus, 800, 600, "IupWindow class - Test 1");		
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

	eventBus.AddListener(EventType::WindowResize, OnWindowResize);
	eventBus.AddListener(EventType::WindowClose, OnWindowClose);
	eventBus.AddListener(EventType::MouseButton, OnMouseButtonClick);


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

	// Part Going 3D
	// -------------
	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 V = glm::mat4(1.0f);
	glm::mat4 P = glm::mat4(1.0f);

	// transform local coordinates to world coordinates
	M = glm::rotate(M, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	V = glm::translate(V, glm::vec3(0.0f, 0.0f, -3.0f));

	// last, define projection (here: perspective projection)
	int scrWidth, scrHeight;
	window.GetWindowRect(scrWidth, scrHeight);
	P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);

	// send all matrices to shaders
	shaderProgram.SetUniformMat4("M", M);
	shaderProgram.SetUniformMat4("V", V);
	shaderProgram.SetUniformMat4("P", P);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	while (!g_exitProgram) {		

		glClear(GL_COLOR_BUFFER_BIT);
		
		// Uniform test
		float alpha = 0.25f;
		shaderProgram.SetUniformFloat("uniformAlpha", alpha);

		shaderProgram.Use();
		mesh.Draw();		

		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
