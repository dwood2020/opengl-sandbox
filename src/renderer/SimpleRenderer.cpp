#include "SimpleRenderer.h"
#include "../glad/glad.h"

#include <iostream>	//FOR DEBUG


SimpleRenderer::SimpleRenderer(): lighting(nullptr), camera(nullptr) { }


SimpleRenderer::SimpleRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, const glm::vec2& windowRect): lighting(&lighting), camera(&camera) {
	
	// register for events
	eventBus.AddListener(EventType::WindowResize, this);

	// initialize rendering
	SetClearColor(glm::vec3(0.0f));
	CalculateViewport(windowRect);

	glEnable(GL_DEPTH_TEST);
}


SimpleRenderer::~SimpleRenderer() { }


void SimpleRenderer::SetClearColor(const glm::vec3& clearColor) {	
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
}



void SimpleRenderer::AddCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return;
	}

	RenderCommand command(modelMatrix, mesh, material);
	renderCommands.push_back(command);
}


void SimpleRenderer::Prepare(void) {
	
	for (RenderCommand& command : renderCommands) {
		// prepare material		
		command.material->Prepare();		

		// get uniform locations into command
		command.pvUniformLocation = command.material->GetShaderProgram()->GetUniformLocation("PV");
		
		command.mUniformLocation = command.material->GetShaderProgram()->GetUniformLocation("M");
		
		// do camera + lighting
		command.material->GetShaderProgram()->SetUniformMat4(command.pvUniformLocation, camera->GetViewProjectionMatrix());
		if (command.material->GetAffectedByLight() == true) {
			
			command.viewPosUniformLocation = command.material->GetShaderProgram()->GetUniformLocation("viewPos");


			lighting->SetUniforms(command.material->GetShaderProgram());

			// first possibility (see RenderCommand + viewPos uniform loc)
			command.material->GetShaderProgram()->SetUniformVec3(command.viewPosUniformLocation, camera->GetPosition());
			
			//TODO: second possibility. Examine which is better
			/*command.material->SetUniform("viewPos", camera->GetPosition());*/
		}
		
		// do model matrix
		command.material->GetShaderProgram()->SetUniformMat4(command.mUniformLocation, command.M);
	}
}


void SimpleRenderer::DoFrame(void) {

	//if (camera->GetViewProjectionMatrixIsDirty() == true) {
	//	for (RenderCommand command : renderCommands) {
	//		command.material->GetShaderProgram()->SetUniformMat4(command.pvUniformLocation, camera->GetViewProjectionMatrix());
	//		if (command.material->GetAffectedByLight() == true) {
	//			command.material->GetShaderProgram()->SetUniformVec3(command.viewPosUniformLocation, camera->GetPosition());
	//		}
	//	}
	//	camera->ResetDirtyState();
	//	//TODO: Make this whole thing EVENT-BASED!
	//}

	//TODO: apply sorting!	
	for (RenderCommand& command : renderCommands) {
		command.material->Bind();
		if (camera->GetViewProjectionMatrixIsDirty() == true) {
			command.material->GetShaderProgram()->SetUniformMat4(command.pvUniformLocation, camera->GetViewProjectionMatrix());
			if (command.material->GetAffectedByLight() == true) {
				command.material->GetShaderProgram()->SetUniformVec3(command.viewPosUniformLocation, camera->GetPosition());
			}

		}
		command.material->GetShaderProgram()->SetUniformMat4(command.mUniformLocation, command.M);
		command.mesh->Draw();
		command.material->Unbind();
	}

	if (camera->GetViewProjectionMatrixIsDirty() == true) {
		camera->ResetDirtyState();
	}


}


void SimpleRenderer::OnEvent(Event& e) {

	if (e.GetType() == EventType::WindowResize) {
		auto& eResize = (WindowResizeEvent&)e;
		glm::vec2 rect = glm::vec2(eResize.GetScreenWidth(), eResize.GetScreenHeight());
		CalculateViewport(rect);

		std::cout << "Window resize event handled in SimpleRenderer" << std::endl;
	}
}


