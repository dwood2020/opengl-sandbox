#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(Lighting& lighting, CameraBase& camera, VoxelScene& scene): 
	lighting(&lighting), camera(&camera), scene(&scene) { }


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::Prepare(void) {
	
}


void VoxelRenderer::DoFrame(void) {
	
}
