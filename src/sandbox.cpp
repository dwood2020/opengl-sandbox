#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "events/EventBus.h"
#include "events/EventListener.hpp"
#include "Keycodes.hpp"

#include "window/IupWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "MeshFactory.h"
#include "Texture.h"
#include "camera/SimpleCamera.h"


#include <chrono>


bool g_exitProgram = false;


void OnKeyEvent(Event& e) {
	if (e.keyCode != KeyCode::None) {
		std::cout << "Key " << (int)e.keyCode << ((e.isKeydown) ? " pressed" : " released") << std::endl;
	}	
	if (e.keyCode == KeyCode::Esc) {
		g_exitProgram = true;
	}
}


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

	glm::vec2 windowRect = window.GetWindowRect();
	glViewport(0, 0, (GLsizei)windowRect.x, (GLsizei)windowRect.y);

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
	Mesh csMesh = meshFactory.MakeCoordinateSystem(2.0f);


	Shader vertexShader(Shader::ReadSourceFromFile("res/vert_texture.glsl").c_str(), GL_VERTEX_SHADER);
	Shader fragmentShader(Shader::ReadSourceFromFile("res/frag_texture.glsl").c_str(), GL_FRAGMENT_SHADER);
	vertexShader.CheckCompilationStatus();
	fragmentShader.CheckCompilationStatus();

	ShaderProgram shaderProgram(vertexShader, fragmentShader);
	shaderProgram.CheckLinkStatus();
	//shaderProgram.Use();	

	// second shader program for coordinate system
	Shader vertexShaderCS(Shader::ReadSourceFromFile("res/coordSystem_vert.glsl").c_str(), GL_VERTEX_SHADER);
	Shader fragmentShaderCS(Shader::ReadSourceFromFile("res/coordSystem_frag.glsl").c_str(), GL_FRAGMENT_SHADER);
	vertexShaderCS.CheckCompilationStatus();
	fragmentShaderCS.CheckCompilationStatus();

	ShaderProgram shaderProgramCS(vertexShaderCS, fragmentShaderCS);
	shaderProgramCS.CheckLinkStatus();
	//shaderProgramCS.Use();
	

	// Textures
	// --------
	Texture tex1 = Texture::GenerateFromFile("res/texture/box.png", GL_NEAREST);


	// Part Going 3D
	// -------------
	glm::mat4 M = glm::mat4(1.0f);
	//glm::mat4 V = glm::mat4(1.0f);
	//glm::mat4 P = glm::mat4(1.0f);

	// transform local coordinates to world coordinates
	//M = glm::rotate(M, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	//V = glm::translate(V, glm::vec3(0.0f, 0.0f, 5.0f) * -1.0f);

	// V and P now via Camera class
	glm::vec3 initialCameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	//ArcballCamera camera(eventBus, xScreen, yScreen, initialCameraPos);
	SimpleCamera camera(eventBus, window.GetWindowRect(), initialCameraPos);
	//camera.SetPosition(glm::vec3(0.0f, 0.0f, 5.0f));
	//ArcballCamera2 camera(eventBus, xScreen, yScreen, initialCameraPos);

	// last, define projection (here: perspective projection)	
	//g_P = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 100.0f);
	//CalcProjectionMatrix(800, 600);

	// send all matrices to shaders
	shaderProgram.Use();
	shaderProgram.SetUniformMat4("M", M);	
	shaderProgram.SetUniformMat4("V", camera.GetViewMatrix());
	shaderProgram.SetUniformMat4("P", camera.GetProjectionMatrix());

	shaderProgramCS.Use();
	shaderProgramCS.SetUniformMat4("M", M);
	shaderProgramCS.SetUniformMat4("V", camera.GetViewMatrix());
	shaderProgramCS.SetUniformMat4("P", camera.GetProjectionMatrix());


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// all steps for cube
		shaderProgram.Use();
		if (camera.GetProjectionMatrixIsDirty()) {
			shaderProgram.SetUniformMat4("P", camera.GetProjectionMatrix());
		}
		if (camera.GetViewMatrixIsDirty()) {
			shaderProgram.SetUniformMat4("V", camera.GetViewMatrix());
		}
				
		tex1.Bind();
		//shaderProgram.SetUniformInt("tex", 0);	//this is needed for blending different textures (materials)
		mesh.Draw();

		glBindTexture(GL_TEXTURE_2D, 0);

		// now all steps for coordsystem
		shaderProgramCS.Use();		
		if (camera.GetProjectionMatrixIsDirty()) {
			shaderProgramCS.SetUniformMat4("P", camera.GetProjectionMatrix());			
			camera.ResetDirtyState();
		}
		if (camera.GetViewMatrixIsDirty()) {
			shaderProgramCS.SetUniformMat4("V", camera.GetViewMatrix());
			camera.ResetDirtyState();
		}
		csMesh.Draw();



		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
