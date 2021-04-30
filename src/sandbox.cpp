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
#include "MeshFactory.h"
#include "Keycodes.hpp"
#include "Texture.h"

#include <chrono>


bool g_exitProgram = false;
glm::mat4 g_P = glm::mat4(1.0f);
bool g_P_isDirty = false;


void OnKeyEvent(Event& e) {
	if (e.keyCode != KeyCode::None) {
		std::cout << "Key " << (int)e.keyCode << ((e.isKeydown) ? " pressed" : " released") << std::endl;
	}	
	if (e.keyCode == KeyCode::Esc) {
		g_exitProgram = true;
	}
}


// Temporary: Re-calc projection matrix after screen resizing
// this may be job of a "camera" in the future?
void CalcProjectionMatrix(int windowW, int windowH) {
	std::cout << "CalcProjectionMatrix called!" << std::endl;
	g_P = glm::perspective(glm::radians(45.0f), (float)windowW / (float)windowH, 1.0f, 100.0f);
	g_P_isDirty = true;
}


void OnWindowResize(Event& e) {
	std::cout << "OnWindowResize called!" << std::endl;
	CalcProjectionMatrix(e.w, e.h);
	glViewport(0, 0, e.w, e.h);
}


// this is now a proof of concept
void OnWindowClose(Event& e) {
	std::cout << "Window Close event received!" << std::endl;
	g_exitProgram = true;
}


void OnMouseButtonClick(Event& e) {
	std::cout << "Mouse button " << ((e.isPressed) ? "clicked" : "released") << ": " << (int)e.mbCode << std::endl;	
}


// tiny utility function for sandbox tests
unsigned int GetUnixTimestamp(void) {
	auto t = std::chrono::system_clock::now();
	return (unsigned int)std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch()).count();
}


int main(int argc, char* argv[]) {

	EventBus eventBus;
	MeshFactory meshFactory;


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
	eventBus.AddListener(EventType::Key, OnKeyEvent);


	glClearColor(0.075f, 0.196f, 0.325f, 1.0f);	
	
	std::string glVersionStr = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersionStr << std::endl;
	window.SetGLVersionLabel(glVersionStr);


	// test of new mesh class
	/*std::vector<glm::vec3> vertices = {
		{-0.5f, -0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
		{-0.5f, 0.5f, 0.0f},
		{0.5f, 0.5f, 0.0f}
	};

	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 1
	};

	Mesh mesh;
	mesh.SetPositionVertices(vertices);
	mesh.SetIndices(indices);
	mesh.Prepare();
	mesh.SetMode(GL_TRIANGLES);*/

	//Mesh mesh = meshFactory.MakeRectangle(1.0f, 1.0f);
	Mesh mesh = meshFactory.MakeCube(1.0f);	


	Shader vertexShader(Shader::ReadSourceFromFile("res/vert_texture.glsl").c_str(), GL_VERTEX_SHADER);
	Shader fragmentShader(Shader::ReadSourceFromFile("res/frag_texture.glsl").c_str(), GL_FRAGMENT_SHADER);
	vertexShader.CheckCompilationStatus();
	fragmentShader.CheckCompilationStatus();

	ShaderProgram shaderProgram(vertexShader, fragmentShader);
	shaderProgram.CheckLinkStatus();
	shaderProgram.Use();	

	// Textures
	// --------
	Texture texBox = Texture::GenerateFromFile("res/texture/box.png");


	// Part Going 3D
	// -------------
	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 V = glm::mat4(1.0f);
	//glm::mat4 P = glm::mat4(1.0f);

	// transform local coordinates to world coordinates
	M = glm::rotate(M, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	V = glm::translate(V, glm::vec3(0.0f, 0.0f, -3.0f));

	// last, define projection (here: perspective projection)
	int scrWidth, scrHeight;
	window.GetWindowRect(scrWidth, scrHeight);
	g_P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);

	// send all matrices to shaders
	shaderProgram.SetUniformMat4("M", M);
	shaderProgram.SetUniformMat4("V", V);
	shaderProgram.SetUniformMat4("P", g_P);


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		// let object rotate
		M = glm::rotate(M, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
		shaderProgram.SetUniformMat4("M", M);
		shaderProgram.SetUniformInt("tex", 0);

		texBox.Bind();

		if (g_P_isDirty) {
			shaderProgram.SetUniformMat4("P", g_P);
			g_P_isDirty = false;
		}

		shaderProgram.Use();
		mesh.Draw();		

		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
