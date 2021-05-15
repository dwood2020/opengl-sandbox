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


void OnWindowResize(Event& e) {
	std::cout << "OnWindowResize called!" << std::endl;
	WindowResizeEvent& eRes = (WindowResizeEvent&)e;
	glViewport(0, 0, eRes.GetScreenWidth(), eRes.GetScreenHeight());
}


// this is now a proof of concept
void OnWindowClose(Event& e) {
	std::cout << "Window Close event received!" << std::endl;
	g_exitProgram = true;
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
	Mesh csMesh = meshFactory.MakeSimpleCoordinateSystem(2.0f);
	Mesh gridMesh = meshFactory.MakeSimpleGrid(10.0f);

	Mesh testMesh = meshFactory.MakeCoordinateSystem();


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

	Shader vertexShaderSimple(Shader::ReadSourceFromFile("res/vert_simple.glsl").c_str(), GL_VERTEX_SHADER);
	Shader fragmentShaderSimple(Shader::ReadSourceFromFile("res/frag_simple.glsl").c_str(), GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgramSimple(vertexShaderSimple, fragmentShaderSimple);
	shaderProgramSimple.CheckLinkStatus();
	

	// Textures
	// --------
	Texture tex1 = Texture::GenerateFromFile("res/texture/box.png", GL_NEAREST);


	// Part Going 3D
	// -------------
	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 Mcube = glm::mat4(1.0f);
	Mcube = glm::translate(Mcube, glm::vec3(0.5f, 0.5f, 0.5f));

	glm::mat4 Mgrid = glm::mat4(1.0f);

	glm::mat4 Mtest = glm::mat4(1.0f);
	
	//glm::mat4 V = glm::mat4(1.0f);
	//glm::mat4 P = glm::mat4(1.0f);

	// transform local coordinates to world coordinates
	//M = glm::rotate(M, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	//V = glm::translate(V, glm::vec3(0.0f, 0.0f, 5.0f) * -1.0f);

	// V and P now via Camera class
	glm::vec3 initialCameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	SimpleCamera camera(eventBus, window.GetWindowRect(), initialCameraPos);

	// send all matrices to shaders
	shaderProgram.Use();
	shaderProgram.SetUniformMat4("M", Mcube);		
	shaderProgram.SetUniformMat4("PV", camera.GetViewProjectionMatrix());

	shaderProgramSimple.Use();
	shaderProgramCS.SetUniformMat4("M", Mgrid);
	shaderProgramCS.SetUniformMat4("PV", camera.GetViewProjectionMatrix());

	shaderProgramCS.Use();
	shaderProgramCS.SetUniformMat4("M", M);	
	shaderProgramCS.SetUniformMat4("PV", camera.GetViewProjectionMatrix());


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// all steps for cube
		shaderProgram.Use();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			shaderProgram.SetUniformMat4("PV", camera.GetViewProjectionMatrix());
		}
						
		tex1.Bind();
		//shaderProgram.SetUniformInt("tex", 0);	//this is needed for blending different textures (materials)
		mesh.Draw();

		glBindTexture(GL_TEXTURE_2D, 0);

		shaderProgramSimple.Use();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			shaderProgramSimple.SetUniformMat4("PV", camera.GetViewProjectionMatrix());			
		}
		gridMesh.Draw();

		testMesh.Draw();

		// now all steps for coordsystem
		shaderProgramCS.Use();		
		if (camera.GetViewProjectionMatrixIsDirty()) {
			shaderProgramCS.SetUniformMat4("PV", camera.GetViewProjectionMatrix());			
			camera.ResetDirtyState();
		}		
		csMesh.Draw();



		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
