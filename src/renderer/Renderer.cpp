#include "Renderer.h"
#include "../glad/glad.h"

#include <iostream>


Renderer::Renderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera): lighting(&lighting), camera(&camera) {
	
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

	// Prepare code from SimpleRenderer
	// --------------------------------


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

	// --------------------------------


}


void Renderer::DoFrame(void) {

	// DoFrame code from SimpleRenderer
	// --------------------------------

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

	// --------------------------------

}



void Renderer::AddCommand(const glm::mat4& modelMatrix, MeshBase* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return;
	}

	RenderCommand command(modelMatrix, mesh, material);
	renderCommands.push_back(command);
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


