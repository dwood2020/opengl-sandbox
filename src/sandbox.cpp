#include <iostream>
#include <vector>
#include "glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "events/EventBus.h"
#include "events/EventListener.hpp"
#include "Keycodes.hpp"
#include "window/IupWindow.h"
#include "shader/Shader.h"
#include "shader/ShaderProgram.h"
#include "shader/ShaderFactory.h"
#include "Mesh.h"
#include "MeshFactory.h"
#include "Texture.h"
#include "camera/SimpleCamera.h"
#include "Lighting.h"
#include "Uniform.h"
#include "material/PhongMaterial.h"
#include "material/FlatMaterial.h"
#include "material/MaterialLibrary.h"

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

	glm::vec2 windowRect = window.GetWindowRect();
	glViewport(0, 0, (GLsizei)windowRect.x, (GLsizei)windowRect.y);

	eventBus.AddListener(EventType::WindowResize, &sandboxListener);
	eventBus.AddListener(EventType::WindowClose, &sandboxListener);


	glClearColor(0.075f, 0.196f, 0.325f, 1.0f);	
	
	std::string glVersionStr = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << glVersionStr << std::endl;
	window.SetGLVersionLabel(glVersionStr);

	

	//Mesh mesh = meshFactory.MakeRectangle(1.0f, 1.0f);
	Mesh mesh = meshFactory.MakeCube(1.0f, true);	
	Mesh gridMesh = meshFactory.MakeSimpleGrid(20.0f);
	Mesh cs3dMesh = meshFactory.MakeCoordinateSystem(2.0f);

	Mesh coneMesh = meshFactory.MakeCone(0.5f, 2.0f, 20);
	Mesh sphereMesh = meshFactory.MakeSphere(0.5f, 20, 40, false);
	Mesh secondSphereMesh = meshFactory.MakeSphere(0.3f, 20, 20, true);


	// test: get phong shader from factory	
	auto woodenBoxProgRef = shaderFactory.MakeDefaultPhongShaderProgram();	
	auto gridShaderProgRef = shaderFactory.MakeDefaultFlatShaderProgram();	
	auto defaultMaterialProgRef = shaderFactory.MakeDefaultPhongShaderProgram();	
	auto coordSystemMaterialProgRef = shaderFactory.MakeDefaultFlatShaderProgram();	


	
	// Textures
	// --------
	Texture tex1 = Texture::GenerateFromFile("res/texture/box.png", GL_NEAREST);
	Texture tex2 = Texture::GenerateFromFile("res/texture/concrete.png", GL_NEAREST);


	// Part Going 3D
	// -------------
	// transform local coordinates to world coordinates	
	glm::mat4 Mcube = glm::mat4(1.0f);
	Mcube = glm::translate(Mcube, glm::vec3(0.5f, 0.5f, 0.5f));

	glm::mat4 Mgrid = glm::mat4(1.0f);
	glm::mat4 Mcs3d = glm::mat4(1.0f);

	glm::mat4 Mcone = glm::mat4(1.0f);
	Mcone = glm::translate(Mcone, glm::vec3(4.0f, 0.0f, 1.0f));

	glm::mat4 Msphere = glm::mat4(1.0f);
	Msphere = glm::translate(Msphere, glm::vec3(-2.0f, 0.0f, -3.0f));

	glm::mat4 MsecondSphere = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 0.0f, -4.0f));

	// move slightly backwards (moving camera backwards = z+, but scene is moved in opposite direction to "move the camera")
	//V = glm::translate(V, glm::vec3(0.0f, 0.0f, 5.0f) * -1.0f);

	// V and P now via Camera class
	glm::vec3 initialCameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	SimpleCamera camera(eventBus, window.GetWindowRect(), initialCameraPos);



	// use lighting class
	Lighting lighting;
	lighting.SetDirection(glm::vec3(-0.8f, -1.2f, -1.0f));	//NOTE: Not exactly pointed towards corner to make sides of cube better visible
	lighting.SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	lighting.SetAmbientFactor(0.4f);

	
	// use new Materials
	PhongMaterial woodenBoxMaterial(woodenBoxProgRef);
	woodenBoxMaterial.SetDiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f));
	woodenBoxMaterial.SetDiffuseTexture(tex1);
	woodenBoxMaterial.SetSpecularColor(glm::vec3(1.0f) * 0.4f);

	FlatMaterial gridMaterial(gridShaderProgRef);
	gridMaterial.SetFlatColor(glm::vec3(0.494f, 0.486f, 0.455f));
	//gridMaterial.SetFlatColor(glm::vec3(1.0f, 0.0f, 0.0f));

	PhongMaterial defaultMaterial(defaultMaterialProgRef);
	defaultMaterial.SetDiffuseColor(glm::vec3(0.1f, 0.9f, 0.2f));
	defaultMaterial.SetSpecularColor(glm::vec3(1.0f) * 0.4f);
	defaultMaterial.SetShininess(32.0f);

	FlatMaterial coordSystemMaterial(coordSystemMaterialProgRef);
	coordSystemMaterial.SetUseColorVertices(true);


	FlatMaterial* flatMaterial1 = materialLibrary.MakeFlatMaterial("flatMaterial1");
	flatMaterial1->SetFlatColor(glm::vec3(1.0f, 0.0f, 0.5f));


	PhongMaterial* phongMaterial1 = materialLibrary.MakePhongMaterial("phongMaterial1");
	phongMaterial1->SetDiffuseColor(glm::vec3(1.0f) * 0.5f);
	phongMaterial1->SetDiffuseTexture(tex2);
	phongMaterial1->SetSpecularColor(glm::vec3(1.0f));


	// send all matrices to shaders

	woodenBoxMaterial.Prepare();
	woodenBoxProgRef->SetUniformMat4(woodenBoxProgRef->GetUniformLocation("M"), Mcube);
	woodenBoxProgRef->SetUniformMat4(woodenBoxProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
	if (woodenBoxMaterial.GetAffectedByLight()) {
		lighting.SetUniforms(woodenBoxProgRef);
		woodenBoxProgRef->SetUniformVec3(woodenBoxProgRef->GetUniformLocation("viewPos"), camera.GetPosition());
	}
	

	gridMaterial.Prepare();
	gridShaderProgRef->SetUniformMat4(gridShaderProgRef->GetUniformLocation("M"), Mgrid);
	gridShaderProgRef->SetUniformMat4(gridShaderProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());

	defaultMaterial.Prepare();
	if (defaultMaterial.GetAffectedByLight()) {
		lighting.SetUniforms(defaultMaterialProgRef);
	}
	
	defaultMaterialProgRef->SetUniformVec3(defaultMaterialProgRef->GetUniformLocation("viewPos"), camera.GetPosition());

	coordSystemMaterial.Prepare();
	coordSystemMaterialProgRef->SetUniformMat4(coordSystemMaterialProgRef->GetUniformLocation("M"), Mcs3d);
	coordSystemMaterialProgRef->SetUniformMat4(coordSystemMaterialProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());


	flatMaterial1->Prepare();
	flatMaterial1->GetShaderProgram()->SetUniformMat4(flatMaterial1->GetShaderProgram()->GetUniformLocation("M"), MsecondSphere);
	flatMaterial1->GetShaderProgram()->SetUniformMat4(flatMaterial1->GetShaderProgram()->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
	if (flatMaterial1->GetAffectedByLight() == true) {
		lighting.SetUniforms(flatMaterial1->GetShaderProgram());
	}

	phongMaterial1->Prepare();
	phongMaterial1->GetShaderProgram()->SetUniformMat4(phongMaterial1->GetShaderProgram()->GetUniformLocation("M"), MsecondSphere);
	phongMaterial1->GetShaderProgram()->SetUniformMat4(phongMaterial1->GetShaderProgram()->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
	phongMaterial1->GetShaderProgram()->SetUniformVec3(phongMaterial1->GetShaderProgram()->GetUniformLocation("viewPos"), camera.GetPosition());
	if (phongMaterial1->GetAffectedByLight()) {
		lighting.SetUniforms(phongMaterial1->GetShaderProgram());
	}
	

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);

	while (!g_exitProgram) {		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// all steps for cube		
		woodenBoxMaterial.Bind();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			woodenBoxProgRef->SetUniformMat4(woodenBoxProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
			woodenBoxProgRef->SetUniformVec3(woodenBoxProgRef->GetUniformLocation("viewPos"), camera.GetPosition());
		}		
		
		//tex1.Bind();
		//shaderProgram.SetUniformInt("tex", 0);	//this is needed for blending different textures (materials)		
		mesh.Draw();
		//Texture::Unbind();
		woodenBoxMaterial.Unbind();



		// draw sphere & cone with default material
		defaultMaterial.Bind();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			defaultMaterialProgRef->SetUniformMat4(defaultMaterialProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
			defaultMaterialProgRef->SetUniformVec3(defaultMaterialProgRef->GetUniformLocation("viewPos"), camera.GetPosition());
		}
		int modelMatrixUniformLocation = defaultMaterialProgRef->GetUniformLocation("M");
		defaultMaterialProgRef->SetUniformMat4(modelMatrixUniformLocation, Msphere);
		sphereMesh.Draw();

		defaultMaterialProgRef->SetUniformMat4(modelMatrixUniformLocation, Mcone);
		coneMesh.Draw();

		defaultMaterial.Unbind();


		// draw grid		
		gridMaterial.Bind();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			gridShaderProgRef->SetUniformMat4(gridShaderProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
		}
		gridMesh.Draw();



		// draw coord system using flat material
		coordSystemMaterial.Bind();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			coordSystemMaterialProgRef->SetUniformMat4(coordSystemMaterialProgRef->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());			
		}
		cs3dMesh.Draw();
		coordSystemMaterial.Unbind();
	

		// draw second sphere
		/*flatMaterial1->Bind();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			flatMaterial1->GetShaderProgram()->SetUniformMat4(flatMaterial1->GetShaderProgram()->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
		}
		secondSphereMesh.Draw();
		flatMaterial1->Unbind();*/
		phongMaterial1->Bind();
		if (camera.GetViewProjectionMatrixIsDirty()) {
			phongMaterial1->GetShaderProgram()->SetUniformMat4(phongMaterial1->GetShaderProgram()->GetUniformLocation("PV"), camera.GetViewProjectionMatrix());
			phongMaterial1->GetShaderProgram()->SetUniformVec3(phongMaterial1->GetShaderProgram()->GetUniformLocation("viewPos"), camera.GetPosition());
		}
		secondSphereMesh.Draw();
		phongMaterial1->Unbind();


		if (camera.GetViewProjectionMatrixIsDirty()) {
			camera.ResetDirtyState();
		}
		window.SwapBuffers();
		window.DoFrame();

		eventBus.Poll();
	}

	return 0;
}
