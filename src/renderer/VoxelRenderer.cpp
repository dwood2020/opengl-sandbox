#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(EventBus& eventBus, Lighting& lighting, CameraBase& camera, const glm::vec2& windowRect, VoxelScene& voxelScene) {
	
	this->lighting = &lighting;
	this->camera = &camera;

	this->voxelScene = &voxelScene;

	// register for events
	eventBus.AddListener(EventType::WindowResize, this);

	// initialize rendering	
	CalculateViewport(windowRect);
}


VoxelRenderer::~VoxelRenderer() { }


void VoxelRenderer::AddMaterial(char blocktype, MaterialBase& material) {
	blockMaterials.insert(std::pair<char, MaterialBase*>(blocktype, &material));
}


void VoxelRenderer::OnEvent(Event& e) {

}


void VoxelRenderer::Prepare(void) {

}


void VoxelRenderer::DoFrame(void) {

}
