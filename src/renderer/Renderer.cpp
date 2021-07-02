#include "Renderer.h"
#include "../glad/glad.h"
#include "../material/MaterialBase.h"

#include <iostream>


Renderer::Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, MaterialLibrary& materialLibrary): 
	lighting(&lighting), camera(&camera), materialLibrary(&materialLibrary) {
	
	// register for events
	eventBus.AddListener(EventType::WindowResize, this);
}


Renderer::~Renderer() { }


void Renderer::OnEvent(Event& e) {
	if (e.GetType() == EventType::WindowResize) {
		auto& eResize = (WindowResizeEvent&)e;
		glm::vec2 rect = glm::vec2(eResize.GetScreenWidth(), eResize.GetScreenHeight());
		CalculateViewport(rect);

		std::cout << "Window resize event handled in Renderer" << std::endl;
	}
}


void Renderer::Init(const glm::vec2& windowRect) {
	CalculateViewport(windowRect);
	
	glEnable(GL_DEPTH_TEST);
}


void Renderer::Prepare(void) {

	MaterialsMap* mats = materialLibrary->GetMaterialsMap();
	
	for (auto it = mats->begin(); it != mats->end(); ++it) {
		MaterialBase* material = it->second;

		// prepare the material
		material->Prepare();

		// do initial set
		material->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());
		if (material->GetAffectedByLight()) {
			material->SetViewPosUniform(camera->GetPosition());
			lighting->SetUniforms(material->GetShaderProgram());
		}

	}

}


void Renderer::DoFrame(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// simple render commands first:

	for (SimpleRenderCommand& command : simpleRenderCommands) {
		command.material->Bind();

		if (camera->GetViewProjectionMatrixIsDirty() == true) {
			command.material->SetViewProjectionMatrixUniform(camera->GetViewProjectionMatrix());

			if (command.material->GetAffectedByLight() == true) {
				command.material->SetViewPosUniform(camera->GetPosition());
			}
		}

		command.material->SetModelMatrixUniform(command.M);
		command.mesh->Draw();
		command.material->Unbind();		
	}

	// voxelscene render commands second:



	if (camera->GetViewProjectionMatrixIsDirty() == true) {
		camera->ResetDirtyState();
	}

}



void Renderer::AddCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return;
	}

	RenderCommand command(modelMatrix, mesh, material);
	renderCommands.push_back(command);
}


void Renderer::AddSimpleCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return;
	}

	SimpleRenderCommand command(modelMatrix, mesh, material);
	simpleRenderCommands.push_back(command);
}


void Renderer::SetClearColor(const glm::vec3& clearColor) {
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}


void Renderer::SetGlPolygonMode(GLenum mode) {
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}



void Renderer::CalculateViewport(const glm::vec2& rect) {
	glViewport(0, 0, (GLsizei)rect.x, (GLsizei)rect.y);
}


