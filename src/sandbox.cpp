#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "events/EventBus.h"
#include "events/EventListener.hpp"
#include "window/IupWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "MeshFactory.h"
#include "Keycodes.hpp"
#include "Texture.h"
#include "Camera.h"

#include <chrono>


bool g_exitProgram = false;
//glm::mat4 g_P = glm::mat4(1.0f);
//bool g_P_isDirty = false;


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
//void CalcProjectionMatrix(int windowW, int windowH) {
//	
//	float w = (float)windowW;
//	float h = (float)windowH;
//
//	// perspective projection
//	g_P = glm::perspective(glm::radians(45.0f), w / h, 1.0f, 100.0f);
//	
//	// orthographic projection
//	/*w = w / 100.0f;
//	h = h / 100.0f;
//	g_P = glm::ortho(-w/2.0f, w/2.0f, -h/2.0f, h/2.0f, 1.0f, 100.0f);*/
//
//	g_P_isDirty = true;
//}


void OnWindowResize(Event& e) {
	std::cout << "OnWindowResize called!" << std::endl;
	/*CalcProjectionMatrix(e.w, e.h);*/
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


// utility listener class for sandbox testing
class SandboxListener : public EventListener {
public:
	void OnEvent(Event& e) override {
		if (e.GetType() == EventType::WindowClose) {
			OnWindowClose(e);
		}
		else if (e.GetType() == EventType::WindowResize) {
			OnWindowResize(e);
		}
		// key and mousebutton event handlers not yet added
	}
};


// tiny utility function for sandbox tests
unsigned int GetUnixTimestamp(void) {
	auto t = std::chrono::system_clock::now();
	return (unsigned int)std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch()).count();
}


int main(int argc, char* argv[]) {

	// utility listener for sandbox
	SandboxListener sandboxListener;

	EventBus eventBus;
	MeshFactory meshFactory;


	IupWindow window(&eventBus, 800, 600, "OpenGL Sandbox - IUP Window");		
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

	eventBus.AddListener(EventType::WindowResize, &sandboxListener);
	eventBus.AddListener(EventType::WindowClose, &sandboxListener);
	eventBus.AddListener(EventType::MouseButton, &sandboxListener);
	eventBus.AddListener(EventType::Key, &sandboxListener);


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
	Mesh mesh = meshFactory.MakeCube(1.0f, true);	


	Shader vertexShader(Shader::ReadSourceFromFile("res/vert_texture.glsl").c_str(), GL_VERTEX_SHADER);
	Shader fragmentShader(Shader::ReadSourceFromFile("res/frag_texture.glsl").c_str(), GL_FRAGMENT_SHADER);
	vertexShader.CheckCompilationStatus();
	fragmentShader.CheckCompilationStatus();

	ShaderProgram shaderProgram(vertexShader, fragmentShader);
	shaderProgram.CheckLinkStatus();
	shaderProgram.Use();	

	// Textures
	// --------
	Texture tex1 = Texture::GenerateFromFile("res/texture/mc/cobblestone.png", GL_NEAREST);


	// Part Going 3D
	// -------------
	glm::mat4 M = glm::mat4(1.0f);
	//glm::mat4 V = glm::mat4(1.0f);
	//glm::mat4 P = glm::mat4(1.0f);

	// transform local coordinates to world coordinates
	M = glm::rotate(M, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	//V = glm::translate(V, glm::vec3(0.0f, 0.0f, 5.0f) * -1.0f);

	// V and P now via Camera class
	Camera camera(eventBus);
	camera.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));


	// last, define projection (here: perspective projection)
	int scrWidth, scrHeight;
	window.GetWindowRect(scrWidth, scrHeight);
	//g_P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);
	//CalcProjectionMatrix(800, 600);

	// send all matrices to shaders
	shaderProgram.SetUniformMat4("M", M);
	//shaderProgram.SetUniformMat4("V", V);
	shaderProgram.SetUniformMat4("V", camera.V);
	//shaderProgram.SetUniformMat4("P", g_P);
	shaderProgram.SetUniformMat4("P", camera.P);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
		tex1.Bind();
		//shaderProgram.SetUniformInt("tex", 0);	//this is needed for blending different textures (materials)


		// let object rotate
		M = glm::rotate(M, 0.01f, glm::vec3(1.0f, 0.0f, 0.0f));
		shaderProgram.SetUniformMat4("M", M);
		

		/*if (g_P_isDirty) {
			shaderProgram.SetUniformMat4("P", g_P);
			g_P_isDirty = false;
		}*/
		if (camera.PIsDirty) {
			shaderProgram.SetUniformMat4("P", camera.P);
			camera.PIsDirty = false;
		}
		if (camera.VIsDirty) {
			shaderProgram.SetUniformMat4("V", camera.V);
			camera.VIsDirty = false;
		}


		shaderProgram.Use();
		mesh.Draw();		

		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
