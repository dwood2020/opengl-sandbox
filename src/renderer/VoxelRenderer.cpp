#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, const glm::vec2& windowRect, VoxelScene& voxelScene) {
	
	this->lighting = &lighting;
	this->camera = &camera;

	this->voxelScene = &voxelScene;

	//// register for events
	//eventBus.AddListener(EventType::WindowResize, this);

	//// initialize rendering	
	//CalculateViewport(windowRect);
}


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::AddMaterial(char blocktype, MaterialBase* material) {
	if (material == nullptr) {
		return;
	}

	blockMaterials.insert(std::pair<char, MaterialBase*>(blocktype, material));
}


void VoxelRenderer::OnEvent(Event& e) {

}


void VoxelRenderer::Prepare(void) {

	// prepare all materials
	for (auto it = blockMaterials.begin(); it != blockMaterials.end(); ++it) {
		
		// add missing uniforms
		it->second->SetUniform("PV", Uniform(camera->GetViewProjectionMatrix()));

		// temp
		it->second->SetUniform("M", Uniform(glm::mat4(1.0f)));

		if (it->second->GetAffectedByLight() == true) {
			it->second->SetUniform("viewPos", Uniform(camera->GetPosition()));			
		}

		it->second->Prepare();

		if (it->second->GetAffectedByLight() == true) {
			lighting->SetUniforms(it->second->GetShaderProgram());
		}
	}
}


void VoxelRenderer::DoFrame(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// iterate over all sections
	for (auto itSection = voxelScene->GetSections().begin(); itSection != voxelScene->GetSections().end(); ++itSection) {

		// iterate over all meshes within each section
		for (auto itMesh = itSection->second->GetMeshes().begin(); itMesh != itSection->second->GetMeshes().end(); ++itMesh) {
			MaterialBase* material = blockMaterials[itMesh->first];
			material->Bind();

			if (camera->GetViewProjectionMatrixIsDirty() == true) {
				material->GetUniform("PV")->UpdateValue(camera->GetViewProjectionMatrix());

				if (material->GetAffectedByLight() == true) {
					material->GetUniform("viewPos")->UpdateValue(camera->GetPosition());
				}
			}

			itMesh->second.Draw();

			material->Unbind();
		}

	}

}
