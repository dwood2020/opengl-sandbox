#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "events/EventBus.h"
#include "events/EventListener.hpp"
#include "events/Keycodes.hpp"
#include "window/IupWindow.h"
#include "shader/Shader.h"
#include "shader/ShaderProgram.h"
#include "shader/ShaderFactory.h"
#include "mesh/StaticMesh.h"
#include "mesh/StaticMeshFactory.h"
#include "mesh/DynamicMesh.h"
#include "Texture.h"
#include "camera/SimpleCamera.h"
#include "Lighting.h"
#include "Uniform.h"
#include "material/PhongMaterial.h"
#include "material/FlatMaterial.h"
#include "material/MaterialLibrary.h"
#include "renderer/SimpleRenderer.h"
#include "voxel/VoxelScene.h"

#include <chrono>


bool g_exitProgram = false;


//void OnWindowResize(Event& e) {
//	std::cout << "OnWindowResize called!" << std::endl;
//	WindowResizeEvent& eRes = (WindowResizeEvent&)e;
//	glViewport(0, 0, eRes.GetScreenWidth(), eRes.GetScreenHeight());
//}


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
		/*else if (e.GetType() == EventType::WindowResize) {
			OnWindowResize(e);
		}*/	
		
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
	StaticMeshFactory meshFactory;

	ShaderFactory shaderFactory;
	MaterialLibrary materialLibrary(&shaderFactory);


	IupWindow window(&eventBus, 800, 600, "OpenGL Sandbox - IUP Window");		
	window.Init(argc, argv);

	window.MakeContextCurrent();

	//now load OpenGL
	if (!gladLoadGL()) {		
		std::cout << "gladLoadGL failed" << std::endl;
		return -1;
	}

	/*glm::vec2 windowRect = window.GetWindowRect();
	glViewport(0, 0, (GLsizei)windowRect.x, (GLsizei)windowRect.y);*/

	glm::vec3 initialCameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	SimpleCamera camera(eventBus, window.GetWindowRect(), initialCameraPos);


	eventBus.AddListener(EventType::WindowResize, &sandboxListener);
	eventBus.AddListener(EventType::WindowClose, &sandboxListener);


	//glClearColor(0.075f, 0.196f, 0.325f, 1.0f);	
	// use lighting class
	Lighting lighting;
	lighting.SetDirection(glm::vec3(-0.8f, -1.2f, -1.0f));	//NOTE: Not exactly pointed towards corner to make sides of cube better visible
	lighting.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	lighting.SetAmbientFactor(0.4f);

	// use renderer
	SimpleRenderer renderer(eventBus, lighting, camera, window.GetWindowRect());
	renderer.SetClearColor(glm::vec3(0.075f, 0.196f, 0.325f));

	
	std::string glVersionStr = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersionStr << std::endl;
	window.SetGLVersionLabel(glVersionStr);

	

	//StaticMesh mesh = meshFactory.MakeRectangle(1.0f, 1.0f);
	StaticMesh mesh = meshFactory.MakeCube(1.0f, true);	
	StaticMesh gridMesh = meshFactory.MakeSimpleGrid(20.0f);
	StaticMesh cs3dMesh = meshFactory.MakeCoordinateSystem(2.0f);

	StaticMesh coneMesh = meshFactory.MakeCone(0.5f, 2.0f, 20);
	StaticMesh sphereMesh = meshFactory.MakeSphere(0.5f, 20, 40, false);
	StaticMesh secondSphereMesh = meshFactory.MakeSphere(0.3f, 20, 20, true);

	
	// Testing voxel classes
	VoxelScene voxelScene;
	voxelScene.SetBlock({ 0,0,1 }, 1);
	voxelScene.SetBlock({ 0,0,3 }, 1);

	char b003 = voxelScene.GetBlock({ 0,0,3 });


	// Test: block template faces in VoxelScene
	glm::mat4 MfaceTemplate = glm::mat4(1.0f);
	MfaceTemplate = glm::translate(MfaceTemplate, glm::vec3(3.0f, 0.0f, -6.0f));

	DynamicMesh templateTestMesh;
	templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), voxelScene.frontFaceTemplate.begin(), voxelScene.frontFaceTemplate.end());
	templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), voxelScene.rightFaceTemplate.begin(), voxelScene.rightFaceTemplate.end());
	templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), voxelScene.rearFaceTemplate.begin(), voxelScene.rearFaceTemplate.end());
	templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), voxelScene.leftFaceTemplate.begin(), voxelScene.leftFaceTemplate.end());
	templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), voxelScene.topFaceTemplate.begin(), voxelScene.topFaceTemplate.end());
	templateTestMesh.GetVerticesPosNorm().insert(templateTestMesh.GetVerticesPosNorm().end(), voxelScene.bottomFaceTemplate.begin(), voxelScene.bottomFaceTemplate.end());
	templateTestMesh.SetGlMode(GL_TRIANGLES);
	templateTestMesh.Prepare();


	// Textures
	// --------
	Texture tex1 = Texture::GenerateFromFile("res/texture/box.png", GL_NEAREST);
	Texture tex2 = Texture::GenerateFromFile("res/texture/concrete.png", GL_NEAREST);


	// Part Going 3D
	// -------------
	// transform local coordinates to world coordinates	
	glm::mat4 Mcube = glm::mat4(1.0f);
	Mcube = glm::translate(Mcube, glm::vec3(0.5f, 0.5f, 0.5f));

	glm::mat4 Mid = glm::mat4(1.0f);	

	glm::mat4 Mcone = glm::mat4(1.0f);
	Mcone = glm::translate(Mcone, glm::vec3(4.0f, 0.0f, 1.0f));

	glm::mat4 Msphere = glm::mat4(1.0f);
	Msphere = glm::translate(Msphere, glm::vec3(-2.0f, 0.0f, -3.0f));

	glm::mat4 MsecondSphere = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f, 0.0f, 1.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	//V = glm::translate(V, glm::vec3(0.0f, 0.0f, 5.0f) * -1.0f);

	// V and P now via Camera class
	

	
	// use new Materials from Material library
	FlatMaterial* flatMaterial1 = materialLibrary.MakeFlatMaterial("flatMaterial1");
	flatMaterial1->SetFlatColor(glm::vec3(1.0f, 0.0f, 0.5f));


	PhongMaterial* phongMaterial1 = materialLibrary.MakePhongMaterial("phongMaterial1");
	phongMaterial1->SetDiffuseColor(glm::vec3(1.0f) * 0.5f);
	phongMaterial1->SetDiffuseTexture(tex2);
	phongMaterial1->SetSpecularColor(glm::vec3(1.0f));


	PhongMaterial* woodenBoxMaterial = materialLibrary.MakePhongMaterial("woodenBoxMaterial");
	woodenBoxMaterial->SetDiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f));
	woodenBoxMaterial->SetDiffuseTexture(tex1);
	woodenBoxMaterial->SetSpecularColor(glm::vec3(1.0f) * 0.4f);

	FlatMaterial* gridMaterial = materialLibrary.MakeFlatMaterial("gridMaterial");
	gridMaterial->SetFlatColor(glm::vec3(0.33f));

	PhongMaterial* defaultMaterial = materialLibrary.MakePhongMaterial("defaultMaterial");
	defaultMaterial->SetDiffuseColor(glm::vec3(0.1f, 0.9f, 0.2f));
	defaultMaterial->SetSpecularColor(glm::vec3(1.0f) * 0.4f);
	defaultMaterial->SetShininess(32.0f);

	FlatMaterial* coordSystemMaterial = materialLibrary.MakeFlatMaterial("coordSystemMaterial");
	coordSystemMaterial->SetUseColorVertices(true);



	renderer.AddCommand(Mid, &gridMesh, gridMaterial);
	renderer.AddCommand(Mid, &cs3dMesh, coordSystemMaterial);
	renderer.AddCommand(MsecondSphere, &secondSphereMesh, phongMaterial1);
	renderer.AddCommand(Msphere, &sphereMesh, defaultMaterial);
	renderer.AddCommand(Mcone, &coneMesh, defaultMaterial);
	renderer.AddCommand(Mcube, &mesh, woodenBoxMaterial);


	renderer.AddCommand(MfaceTemplate, &templateTestMesh, defaultMaterial);

	
	renderer.Prepare();

	//TEST
	std::cout << "sizeof(bool): " << sizeof(bool) << std::endl;
	std::cout << "sizeof(char): " << sizeof(char) << std::endl;
	std::cout << "sizeof(char*): " << sizeof(char*) << std::endl;
	std::cout << "sizeof(int*): " << sizeof(int*) << std::endl;



	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		renderer.DoFrame();

		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
