#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(Lighting& lighting, CameraBase& camera, VoxelScene& scene): 
	lighting(&lighting), camera(&camera), scene(&scene) {

	//TODO: Add default material for -1 or 1
}


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::AddMaterial(char blocktype, MaterialBase* material) {
	if (material == nullptr) {
		return;
	}

	blockMaterials.insert(std::pair<char, MaterialBase*>(blocktype, material));
}


void VoxelRenderer::Prepare(void) {
	
	// prepare materials
	for (auto it = blockMaterials.begin(); it != blockMaterials.end(); ++it) {
		MaterialBase* material = it->second;

		material->SetUniform("PV", Uniform(camera->GetViewProjectionMatrix()));

		if (material->GetAffectedByLight()) {
			material->SetUniform("viewPos", Uniform(camera->GetPosition()));
		}

		material->Prepare();

		if (material->GetAffectedByLight()) {
			lighting->SetUniforms(material->GetShaderProgram());
		}
	}

}


void VoxelRenderer::DoFrame(void) {
	
}
