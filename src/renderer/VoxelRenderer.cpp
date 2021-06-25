#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(Lighting& lighting, CameraBase& camera, VoxelScene& scene): 
	lighting(&lighting), camera(&camera), scene(&scene) { }


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::AddMaterial(char blocktype, MaterialBase* material) {
	if (material == nullptr) {
		return;
	}

	blockMaterials.insert(std::pair<char, MaterialBase*>(blocktype, material));
}


void VoxelRenderer::Prepare(void) {
	
}


void VoxelRenderer::DoFrame(void) {
	
}
