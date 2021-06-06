#include "SimpleRenderer.h"


SimpleRenderer::SimpleRenderer(): lighting(nullptr), camera(nullptr) { }


SimpleRenderer::SimpleRenderer(Lighting& lighting, CameraBase& camera): lighting(&lighting), camera(&camera) { }


SimpleRenderer::~SimpleRenderer() { }



void SimpleRenderer::AddCommand(const glm::mat4& modelMatrix, Mesh* mesh, MaterialBase* material) {
	if (mesh == nullptr || material == nullptr) {
		//TODO ASSERT or check if passing arg by reference is better option
		return;
	}

	RenderCommand command(modelMatrix, mesh, material);
	renderCommands.push_back(command);
}


void SimpleRenderer::PrepareCommands(void) {
	
	for (RenderCommand command : renderCommands) {
		// prepare material		
		command.material->Prepare();		

		// get uniform locations into command
		command.pvUniformLocation = command.material->GetShaderProgram()->GetUniformLocation("PV");
		command.viewPosUniformLocation = command.material->GetShaderProgram()->GetUniformLocation("viewPos");
		command.mUniformLocation = command.material->GetShaderProgram()->GetUniformLocation("M");
		
		// do camera + lighting
		command.material->GetShaderProgram()->SetUniformMat4(command.pvUniformLocation, camera->GetViewProjectionMatrix());
		if (command.material->GetAffectedByLight() == true) {
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


void SimpleRenderer::ExecuteCommands(void) {

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
	unsigned int ctr = 0;
	for (RenderCommand command : renderCommands) {
		command.material->Bind();
		if (camera->GetViewProjectionMatrixIsDirty() == true) {
			command.material->GetShaderProgram()->SetUniformMat4(command.pvUniformLocation, camera->GetViewProjectionMatrix());
			if (command.material->GetAffectedByLight() == true) {
				command.material->GetShaderProgram()->SetUniformVec3(command.viewPosUniformLocation, camera->GetPosition());
			}

			// this is super dirty
			ctr += 1;
			if (ctr == renderCommands.size() - 1) {
				camera->ResetDirtyState();
			}
		}
		command.material->GetShaderProgram()->SetUniformMat4(command.mUniformLocation, command.M);
		command.mesh->Draw();
		command.material->Unbind();
	}



}

