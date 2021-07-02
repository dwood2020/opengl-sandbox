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
//#include "renderer/SimpleRenderer.h"
#include "voxel/VoxelScene.h"
//#include "renderer/RendererMaster.h"
#include "renderer/Renderer.h"

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
	//TODO: Move this into RendererMaster
	if (!gladLoadGL()) {		
		std::cout << "gladLoadGL failed" << std::endl;
		return -1;
	}


	glm::vec3 initialCameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	SimpleCamera camera(eventBus, window.GetWindowRect(), initialCameraPos);


	eventBus.AddListener(EventType::WindowResize, &sandboxListener);
	eventBus.AddListener(EventType::WindowClose, &sandboxListener);


	//glClearColor(0.075f, 0.196f, 0.325f, 1.0f);	
	// use lighting class
	Lighting lighting;
	lighting.SetDirection(glm::vec3(-0.8f, -1.2f, -1.0f));	//NOTE: Not exactly pointed towards corner to make sides of cube better visible
	lighting.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	lighting.SetAmbientFactor(0.5f);

	// use renderer
	//SimpleRenderer renderer(eventBus, lighting, camera);

	Renderer renderer(eventBus, lighting, camera, materialLibrary);	
	renderer.SetClearColor(glm::vec3(0.075f, 0.196f, 0.325f));
	renderer.Init(window.GetWindowRect());

	/*RendererMaster rendererMaster(eventBus, camera);
	rendererMaster.AddRenderer(renderer);
	
	rendererMaster.InitRenderState(window.GetWindowRect());
	rendererMaster.SetClearColor(glm::vec3(0.075f, 0.196f, 0.325f));*/

	
	std::string glVersionStr = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersionStr << std::endl;
	window.SetGLVersionLabel(glVersionStr);

	

	//StaticMesh mesh = meshFactory.MakeRectangle(1.0f, 1.0f);
	StaticMesh mesh = meshFactory.MakeCube(1.0f, true);	
	StaticMesh gridMesh = meshFactory.MakeSimpleGrid(20.0f);
	StaticMesh cs3dMesh = meshFactory.MakeCoordinateSystem(2.0f);

	StaticMesh coneMesh = meshFactory.MakeCone(0.5f, 2.0f, 20);
	StaticMesh sphereMesh = meshFactory.MakeSphere(0.5f, 20, 40, true);
	StaticMesh secondSphereMesh = meshFactory.MakeSphere(0.3f, 20, 20, true);

	
	// Testing voxel classes
	VoxelScene voxelScene;
	voxelScene.SetBlock({ 0,0,1 }, 1);
	voxelScene.SetBlock({ 2,0,3 }, 1);
	voxelScene.SetBlock({ 12,0,0 }, 2);
	voxelScene.SetBlock({ 12,1,0 }, 3);
	voxelScene.SetBlock({ -4,-4,-4 }, 2);
	voxelScene.SetBlock({ -1,0,0 }, 4);
	char b003 = voxelScene.GetBlock({ 2,0,3 });
	
	voxelScene.GenerateMeshes();


	

	// Textures
	// --------
	Texture tex1 = Texture::GenerateFromFile("res/texture/box.png", GL_NEAREST);
	Texture tex2 = Texture::GenerateFromFile("res/texture/concrete.png", GL_NEAREST);


	// Part Going 3D
	// -------------
	// transform local coordinates to world coordinates	
	glm::mat4 Mcube = glm::mat4(1.0f);
	//Mcube = glm::translate(Mcube, glm::vec3(0.5f, 0.5f, 0.5f));
	Mcube = glm::translate(Mcube, glm::vec3(-4.0f, 0.0f, -3.0f));

	glm::mat4 Mid = glm::mat4(1.0f);	

	glm::mat4 Mcone = glm::mat4(1.0f);
	Mcone = glm::translate(Mcone, glm::vec3(0.0f, 0.0f, -3.0f));

	glm::mat4 Msphere = glm::mat4(1.0f);
	Msphere = glm::translate(Msphere, glm::vec3(-2.0f, 0.0f, -3.0f));

	glm::mat4 MsecondSphere = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, -3.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	//V = glm::translate(V, glm::vec3(0.0f, 0.0f, 5.0f) * -1.0f);

	// V and P now via Camera class
	

	
	// use new Materials from Material library
	FlatMaterial* flatMaterial1 = materialLibrary.MakeFlatMaterial(100);
	flatMaterial1->SetFlatColor(glm::vec3(1.0f, 0.0f, 0.5f));


	PhongMaterial* phongMaterial1 = materialLibrary.MakePhongMaterial(101);
	phongMaterial1->SetDiffuseColor(glm::vec3(1.0f) * 0.5f);
	phongMaterial1->SetDiffuseTexture(tex2);
	phongMaterial1->SetSpecularColor(glm::vec3(1.0f));


	PhongMaterial* woodenBoxMaterial = materialLibrary.MakePhongMaterial(102);
	woodenBoxMaterial->SetDiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f));
	woodenBoxMaterial->SetDiffuseTexture(tex1);
	woodenBoxMaterial->SetSpecularColor(glm::vec3(1.0f) * 0.4f);

	FlatMaterial* gridMaterial = materialLibrary.MakeFlatMaterial(200);
	gridMaterial->SetFlatColor(glm::vec3(0.33f));

	PhongMaterial* defaultMaterial = materialLibrary.MakePhongMaterial(1);
	defaultMaterial->SetDiffuseColor(glm::vec3(0.5f));
	defaultMaterial->SetSpecularColor(glm::vec3(1.0f) * 0.3f);
	defaultMaterial->SetShininess(32.0f);

	FlatMaterial* coordSystemMaterial = materialLibrary.MakeFlatMaterial(201);
	coordSystemMaterial->SetUseColorVertices(true);

	PhongMaterial* yellowDebugMaterial = materialLibrary.MakePhongMaterial(2);
	yellowDebugMaterial->SetDiffuseColor(glm::vec3(0.8f, 0.8f, 0.1f));
	yellowDebugMaterial->SetSpecularColor(glm::vec3(0.6f));

	PhongMaterial* greenDebugMaterial = materialLibrary.MakePhongMaterial(3);
	greenDebugMaterial->SetDiffuseColor(glm::vec3(0.1f, 0.9f, 0.2f));
	greenDebugMaterial->SetSpecularColor(glm::vec3(1.0f) * 0.4f);
	greenDebugMaterial->SetShininess(32.0f);	

	PhongMaterial* pinkDebugMaterial = materialLibrary.MakePhongMaterial(4);
	pinkDebugMaterial->SetDiffuseColor(glm::vec3(1.0f, 0.0f, 1.0f));
	pinkDebugMaterial->SetSpecularColor(glm::vec3(1.0f) * 0.4f);



	renderer.AddSimpleCommand(Mid, &gridMesh, gridMaterial);
	renderer.AddSimpleCommand(Mid, &cs3dMesh, coordSystemMaterial);
	renderer.AddSimpleCommand(MsecondSphere, &secondSphereMesh, phongMaterial1);
	renderer.AddSimpleCommand(Msphere, &sphereMesh, defaultMaterial);
	renderer.AddSimpleCommand(Mcone, &coneMesh, greenDebugMaterial);
	renderer.AddSimpleCommand(Mcube, &mesh, woodenBoxMaterial);



	renderer.AddVoxelScene(voxelScene, pinkDebugMaterial);
	renderer.AddBlockMaterialMapping(1, defaultMaterial);
	renderer.AddBlockMaterialMapping(2, yellowDebugMaterial);
	renderer.AddBlockMaterialMapping(3, greenDebugMaterial);


	/*std::map<char, MaterialBase*> dummyMaterials;
	dummyMaterials.insert(std::pair<char, MaterialBase*>(1, defaultMaterial));
	dummyMaterials.insert(std::pair<char, MaterialBase*>(2, yellowDebugMaterial));
	dummyMaterials.insert(std::pair<char, MaterialBase*>(3, greenDebugMaterial));
	
	
	for (auto sectionIt = voxelScene.GetSections().begin(); sectionIt != voxelScene.GetSections().end(); ++sectionIt) {

		for (auto meshIt = sectionIt->second->GetMeshes().begin(); meshIt != sectionIt->second->GetMeshes().end(); ++meshIt) {			
			renderer.AddSimpleCommand(Mid, &meshIt->second, dummyMaterials[meshIt->first]);
		}

	}*/


	renderer.Prepare();
	//rendererMaster.PrepareRenderers();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		renderer.DoFrame();
		//rendererMaster.DoFrame();

		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
